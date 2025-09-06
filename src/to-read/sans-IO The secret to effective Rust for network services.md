---
title: "sans-IO: The secret to effective Rust for network services"
source: "https://www.firezone.dev/blog/sans-io"
author:
published: July 2
created: 2025-07-31
description: "sans-IO: The secret to effective Rust for network services"
tags:
  - "clippings"
---
![Firezone logo light](https://www.firezone.dev/_next/image?url=%2Fimages%2Flogo-main-light-primary.svg&w=384&q=75)

At Firezone, we use Rust <sup><a href="https://www.firezone.dev/blog/#user-content-fn-1">1</a></sup> to build secure remote access that scales, be it from your Android phone, MacOS computer or Linux server. At the core of each app sits a connectivity library — aptly named [`connlib`](https://www.github.com/firezone/firezone/tree/main/rust/connlib) — that manages network connections and WireGuard tunnels to secure your traffic. After several iterations, we’ve landed on a design that we are extremely happy with. It gives us fast and exhaustive tests, deep customisation and overall high assurance that it does what we want it to do.

`connlib` is built in Rust and the design we are talking about is known as sans-IO. Rust's premise of speed and memory-safety makes it a great choice for building network services. Most parts of our Rust stack aren't particularly surprising: We use the `tokio` runtime for asynchronous tasks, `tungstenite` for WebSockets, `boringtun` for the WireGuard implementation, `rustls` to encrypt traffic with the API, etc. Yet, once you go beneath the surface of the library, you will discover something that is perhaps unusual: There are almost no calls to `tokio::spawn`, all communication is multiplexed via a single UDP socket and the same APIs appear to repeat themselves across various layers:`handle_timeout`, `poll_transmit`, `handle_input`, and so on.

These are the tell-tale signs of a sans-IO design. Instead of sending and receiving bytes via a socket in multiple places, our protocols are implemented as pure state machines. Even time is abstracted away: every function that needs to know the current time receives an `Instant` parameter instead of calling `Instant::now` itself. This pattern isn't something that we invented! The Python world even has a dedicated [website](https://sans-io.readthedocs.io/) about it. In Rust, it is used by libraries such as:

- [`quinn`](https://github.com/quinn-rs/quinn/tree/main/quinn-proto), an independent QUIC implementation.
- [`quiche`](https://github.com/cloudflare/quiche/tree/master/quiche), cloudflare's QUIC implementation.
- [`str0m`](https://github.com/algesten/str0m), a sans-IO WebRTC implementation.

In this post, we'll go over some of the problems with doing IO the traditional way, followed by transitioning that to a sans-IO design and the reasons why we think it is a good idea. As it turns out, Rust lends itself particularly well to this pattern.

## Rust's async model & the "function colouring" debate

If you've been around the Rust space for a while, you will have likely come across the "function colouring" debate. In a nutshell, it discusses the constraint that async functions can only be called from other async functions, thus "colouring" them. There are various takes on this but what stands out for me is that the ability to suspend execution and resume later is a pretty important part of function's API contract. The fact that Rust enforces this at compile-time is a good thing.

A result of this constraint is that an async function deep down in your stack "forces" every calling function to also become async in order to `.await` the inner function. This can be problematic if the code you want to call isn't actually yours but a dependency that you are pulling in.

Some people see this as a problem, and they would like to write code that is agnostic over the "asyncness" of their dependencies. That concern has merit. Ultimately, at the very bottom of each async call stack sits a `Future` that needs to suspend on something. Usually, this is some form of IO, like writing to a socket, reading from a file, waiting for time to advance, etc. The majority of async functions however don't actually perform async work themselves. Instead, they are only async because they depend on other async functions. The code around those inner async functions would usually also work in a blocking context, but the author of your dependency happened to pick the async variant.

Let's look at an example of this problem. Firezone's connectivity library `connlib` uses [ICE](https://datatracker.ietf.org/doc/html/rfc8445) for NAT traversal and as part of that, we utilise STUN to discover our server-reflexive candidate, i.e. our public address. STUN is a binary message format and a STUN binding is a pretty simple protocol: Send a UDP packet to server, server notes the IP + port it sees as the sending socket and send a UDP packet back containing that address.

Here is how we could implement this using `tokio` 's `UdpSocket` (thank you to Cloudflare for the public STUN server):

```rust
#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let socket = UdpSocket::bind("0.0.0.0:0").await?;
    socket.connect("stun.cloudflare.com:3478").await?;
    socket.send(&make_binding_request()).await?;

    let mut buf = vec![0u8; 100];
    let num_read = socket.recv(&mut buf).await?;
    let address = parse_binding_response(&buf[..num_read]);

    println!("Our public IP is: {address}");

    Ok(())
}
```

This could be also be written using blocking IO from the standard library:

```rust
fn main() -> anyhow::Result<()> {
    let socket = UdpSocket::bind("0.0.0.0:0")?;
    socket.connect("stun.cloudflare.com:3478")?;
    socket.send(&make_binding_request())?;

    let mut buf = vec![0u8; 100];
    let num_read = socket.recv(&mut buf)?;
    let address = parse_binding_response(&buf[..num_read]);

    println!("Our public IP is: {address}");

    Ok(())
}
```

You can find all of these snippets as working programs in the following repository: [https://github.com/firezone/sans-io-blog-example](https://github.com/firezone/sans-io-blog-example).

Notice how this code is virtually identical apart from the use of `async`? If we wanted to write a library that allows you to perform STUN, we'd have to decide on one of them or include both. There are lots of opinions out there as to what the "best" way of solving this duplication is. Writing sans-IO code is one of them.

## Introducing sans-IO

The core idea of sans-IO is similar to the dependency inversion principle from the OOP world. Whilst some OOP code out there might be a bit extreme in terms of following patterns (looking at you [`AbstractSingletonProxyFactoryBean`](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/aop/framework/AbstractSingletonProxyFactoryBean.html)), I've found it helpful to explicitly spell some of these things out to really get to the bottom of a particular design.

The dependency inversion principle says that policies (what to do) should not depend on implementation details (how to do it). Instead, both components should depend and communicate via abstractions. In other words, the piece of code that decides to send a message on the network (i.e. the policy) should not depend on the code that actually sends the message (i.e. the implementation).

That is the heart of the issue in the above example: We are composing our policy code on top of a UDP socket and thus, forcing everything upwards to either be `async` in the `tokio` example or deal with blocking IO in the `std` case. The policy code is the same, yet it is the one we want to test and perhaps share with others via libraries, regardless of whether or not we use blocking or non-blocking IO.

## Applying dependency inversion

How do we apply the dependency inversion principle then? We introduce abstractions! When we call `UdpSocket::send`, what data are we actually passing? The payload, a `SocketAddr` and — implicitly — the socket itself. The socket can also be identified by means of a `SocketAddr`: The one we bound to earlier in our application. Let's package these three things up into an abstraction. Meet `Transmit`:

```rust
pub struct Transmit {
    dst: SocketAddr,
    payload: Vec<u8>
}
```

Anywhere where we'd like to send data over our `UdpSocket`, we should instead emit a `Transmit`. But that is only one half of the solution. Where does the `Transmit` go? We need to execute this `Transmit` somewhere! This is the 2nd half of any sans-IO application. Recall the definition of the dependency-inversion principle: Policies should not depend on implementations, instead both should depend on abstractions. `Transmit` is our abstraction, and we already know that we need to rewrite our policy code to use it. The actual implementation details, i.e. our `UdpSocket` also needs to be made aware of our new abstraction.

This is where event loops come in. sans-IO code needs to be "driven", almost similarly as to how a `Future` in Rust is lazy and needs to be polled by a runtime to make progress.

Event loops are the implementation of our side-effects and will actually call `UdpSocket::send`. That way, the rest of the code turns into a state machine that only expresses, what should happen at a given moment.

### The state machine

The state machine diagram for our STUN binding request looks like this:

![A UML state diagram for a STUN binding request.](https://www.firezone.dev/_next/image?url=%2Fimages%2Fblog%2Fsans-io%2Fstun-binding-state-machine1.svg&w=1080&q=75)

Without executing the side-effect of sending a message directly, we need to rewrite our code to resemble what it actually is: This state machine. As we can see in our diagram, we have 2 states (not counting entry and exit states):`Sent` & `Received`. These are mutually-exclusive, so we can model them as an enum:

```rust
enum State {
    Sent,
    Received { address: SocketAddr },
}
```

Now, that we've laid out our data structure, let's add some functionality to it!

```rust
struct StunBinding {
    state: State,
    buffered_transmits: VecDeque<Transmit>,
}

impl StunBinding {
    fn new(server: SocketAddr) -> Self {
        Self {
            state: State::Sent,
            buffered_transmits: VecDeque::from([Transmit {
                dst: server,
                payload: make_binding_request(),
            }]),
        }
    }

    fn handle_input(&mut self, packet: &[u8]) {
        // Error handling is left as an exercise to the reader ...
        let address = parse_binding_response(packet);

        self.state = State::Received { address };
    }

    fn poll_transmit(&mut self) -> Option<Transmit> {
        self.buffered_transmits.pop_front()
    }

    fn public_address(&self) -> Option<SocketAddr> {
        match self.state {
            State::Sent => None,
            State::Received { address } => Some(address),
        }
    }
}
```

The `handle_input` function is like the inverse to `Transmit`. We will use it to feed incoming data to our state machine, i.e. the result of `UdpSocket::recv`. We also add a few auxiliary functions to actually construct a new instance of our state machine and to query things from it. With this in place, we now have a state machine that models the behaviour of our program without performing any IO itself.

### The event loop

Without an event loop, this state machine does nothing. For this example, we can get away with a pretty simple event loop:

```rust
fn main() -> anyhow::Result<()> {
    let socket = UdpSocket::bind("0.0.0.0:0")?;
    let server = "stun.cloudflare.com:3478"
        .to_socket_addrs()?
        .next()
        .context("Failed to resolve hostname")?;
    let mut binding = StunBinding::new(server);

    let address = loop {
        if let Some(transmit) = binding.poll_transmit() {
            socket.send_to(&transmit.payload, transmit.dst)?;
            continue;
        }

        let mut buf = vec![0u8; 100];
        let num_read = socket.recv(&mut buf)?;

        binding.handle_input(&buf[..num_read]);

        if let Some(address) = binding.public_address() {
            break address;
        }
    };

    println!("Our public IP is: {address}");

    Ok(())
}
```

Notice how the event loop is slightly more generic than the previous versions? The event loop does not make any assumptions about the details of the STUN binding protocol. It doesn't know that it is request-response for example! From the event loop's perspective, multiple message could be necessary before we can figure out our public address.

UDP is an unreliable protocol, meaning our packets could get lost in transit. To mitigate this, STUN mandates retransmission timers. As it turns out, adding time to this event loop is fairly trivial.

### Abstracting time

What do we mean when we talk about abstracting time? In most cases, especially in network protocols, access to the current time is needed to check whether some amount of time has passed. For example, has it been more than 5s since we sent our request? Another common one is keep-alive messages: Has it been more than 30s since we sent our last keep-alive?

In all these cases, we don't actually need to know the current *wall clock* time. All we need is a `Duration` to a previous point in time. Rust provides us with a very convenient abstraction here: `Instant`. `Instant` doesn't expose the current time, but it allows us to measure the `Duration` between two `Instant` s. We can extend our state machine with two APIs that are generic enough to cover all our time-based needs: `poll_timeout` and `handle_timeout`:

```rust
impl StunBinding {
    // ...

    /// Notifies \`StunBinding\` that time has advanced to \`now\`.
    fn handle_timeout(&mut self, now: Instant) {}

    /// Returns the timestamp when we next expect \`handle_timeout\` to be called.
    fn poll_timeout(&self) -> Option<Instant> {
        None
    }

    // ...
}
```

Similar to `handle_input` and `poll_timeout`, these APIs are the abstraction between our protocol code and the event loop:

- `poll_timeout`: Used by the event loop to schedule a timer for a wake-up.
- `handle_timeout`: Used by the event loop to notify the state machine that a timer has expired.

For demonstration purposes, let's say we want to send a new binding request every 5s after we have received the last one. Here is how one could implement this:

```rust
impl StunBinding {
    // ...

    /// Notifies \`StunBinding\` that time has advanced to \`now\`.
    fn handle_timeout(&mut self, now: Instant) {
        let last_received_at = match self.state {
            State::Sent => return,
            State::Received { at, .. } => at,
        };

        if now.duration_since(last_received_at) < Duration::from_secs(5) {
            return;
        }

        self.buffered_transmits.push_front(Transmit {
            dst: self.server,
            payload: make_binding_request(),
        });
        self.state = State::Sent;
    }

    /// Returns the timestamp when we next expect \`handle_timeout\` to be called.
    fn poll_timeout(&self) -> Option<Instant> {
        match self.state {
            State::Sent => None,
            State::Received { at, .. } => Some(at + Duration::from_secs(5)),
        }
    }

    // ...
}
```

The only other changes I've made are adding an `at` field to the `State::Received` variant that gets set to the current time upon `handle_input`:

```rust
impl StunBinding {
    fn handle_input(&mut self, packet: &[u8], now: Instant) {
        let address = parse_binding_response(packet);

        self.state = State::Received { address, at: now };
    }
}
```

This is an updated version of our state diagram:

![A UML state diagram for a STUN binding request that is being refreshed every 5s.](https://www.firezone.dev/_next/image?url=%2Fimages%2Fblog%2Fsans-io%2Fstun-binding-state-machine2.svg&w=1080&q=75)

The event loop also changed slightly. Instead of exiting once we know our public IP, we'll now loop until the user quits the program:

```rust
loop {
        if let Some(transmit) = binding.poll_transmit() {
            socket.send_to(&transmit.payload, transmit.dst).await?;
            continue;
        }

        let mut buf = vec![0u8; 100];

        tokio::select! {
            Some(time) = &mut timer => {
                binding.handle_timeout(time);
            },
            res = socket.recv(&mut buf) => {
                let num_read = res?;
                binding.handle_input(&buf[..num_read], Instant::now());

            }
        }

        timer.reset_to(binding.poll_timeout());

        if let Some(address) = binding.public_address() {
            println!("Our public IP is: {address}");
        }
    }
```

## The premise of sans-IO

So far, all of this seems like a very excessive overhead for sending a few UDP packets back and forth. Surely, the 10 line example introduced at the start is preferable over this state machine and the event loop! The example might be, but recall the debate around function colouring. In a code snippet without dependencies like the above example, using `async` seems like a no-brainer and really easy. The problem arises once you want to bring in dependencies. Composing your functionality (i.e. policy) on top of those dependencies imposes their decisions around async vs blocking IO on you. Libraries like `str0m` or `quinn-proto` which are written in the sans-IO way don't do that. Instead, they are pure state machines and thus the decision about async vs blocking IO or which async runtime to use is deferred to the application.

Freedom to use either blocking or non-blocking IO isn't the only benefit to this. sans-IO design also compose very well, tend to have very flexible APIs, are easy to test and play well with Rust's features. Let's explore these additional benefits one by one.

### Easy composition

Take another look at the API of `StunBinding`. The main functions exposed to the event loop are: `handle_timeout`, `handle_input`, `poll_transmit` and `poll_timeout`. None of these are specific to the domain of STUN! Most network protocols can be implemented with these or some variation of them. As a result, it is very easy to compose these state machines together: want to query 5 STUN servers for your public IP? No problem. Just make 5 `StunBinding` s and call them in order <sup><a href="https://www.firezone.dev/blog/#user-content-fn-4">2</a></sup>.

In the case of Firezone, you can see this in the example of [`snownet`](https://github.com/firezone/firezone/tree/main/rust/connlib/snownet), a library that combines ICE and WireGuard and thereby exposes "magic" IP tunnels that work in any network setup to the rest of the application.

`snownet` builds on top of `str0m`, a sans-IO WebRTC library and `boringtun`, an (almost <sup><a href="https://www.firezone.dev/blog/#user-content-fn-3">3</a></sup>) sans-IO WireGuard implementation. We don’t need the majority of the WebRTC stack though. The only thing we are interested in is the `IceAgent` which implements [RFC 8445](https://datatracker.ietf.org/doc/html/rfc8445). ICE uses a clever algorithm that ensures two agents, deployed into arbitrary network environments find the most optimal communication path to each other. The result of ICE is a pair of socket addresses that we then use to setup a WireGuard tunnel. Because `str0m` is built in a sans-IO fashion, only using the `IceAgent` is shockingly trivial: you simply only import that part of the library and compose its state machine into your existing code. In `snownet`, a [connection](https://github.com/firezone/firezone/blob/a5b7507932e9d27e3fc9ed5be7428b9937f2f828/rust/connlib/snownet/src/node.rs#L1289-L1306) simply houses an `IceAgent` and a wireguard tunnel, dispatching incoming messages to either one or the other.

### Flexible APIs

sans-IO code needs to be "driven" by an event loop of some sorts because it "just" expresses the state of the system but doesn’t cause any side-effects itself. The event loop is responsible for "querying" the state (like `poll_transmit`), executing it and also passing new input to the state machine (`handle_timeout` and `handle_input`). To some people, this may appear as unnecessary boilerplate but it comes with a great benefit: flexibility.

- Want to make use of `sendmmsg` to reduce the number of syscalls when sending packets? No problem.
- Want to multiplex multiple protocols over a single socket? No problem.

Writing the event loop yourself is an opportunity to be able to tune our code to exactly what we want it to do. This also makes maintenance easier for library authors: They can focus on correctly implementing protocol functionality instead of having debates around async runtimes or exposing APIs to set socket options.

A good example here is `str0m` ’s stance on enumerating network interfaces: This is an IO concern and up to the application on how to achieve it. `str0m` only provides an API to add the socket addresses as an ICE candidate to the current state. As a result, we are able to easily implement optimisations such as gathering TURN candidates prior to any connection being made, thus reducing Firezone's connection-setup latency.

In ICE, both parties gather candidates (sockets) and then test connectivity between them. See [https://datatracker.ietf.org/doc/html/rfc8445#section-5.1.1](https://datatracker.ietf.org/doc/html/rfc8445#section-5.1.1) for details.

### Testing at the speed of light

sans-IO code is essentially side-effect free and thus lends itself extremely well for (unit) tests. Due to sockets and time being abstracted away, it becomes a breeze to write tests that advance time by 5 minutes in an instant. All we need to do is pass a modified `Instant` to our function and assert, how the code behaves. To see a real world example of this,[check out](https://github.com/firezone/firezone/blob/53557f46e452c0fe5195a4326873753a356c6005/rust/connlib/snownet/tests/lib.rs#L123-L127) how we test that `snownet` closes idle connections after 5 minutes.

Similarly, actually sending data over a socket takes (a little bit of) time and more importantly, requires allocation of ports etc. In a sans-IO world, "sending data" in a test is as simple as taking a `Transmit` from party B and calling `handle_input` on the state of party A. No need to go through a network socket!

At Firezone, we took this idea one step further. We implemented a reference state machine that describes how we want `connlib` to work. This reference state machine is used as the source of truth in our tests. We then leverage `proptest` 's support for [state machine testing](https://proptest-rs.github.io/proptest/proptest/state-machine.html) to deterministically sample and execute thousands of scenarios on every CI run and compare the reference state machine with `connlib` 's actual state. The details of this go beyond the scope of this post, so stay tuned for a followup about that topic in particular too! The key take-away here is that a sans-IO design enables these kind of tests.

### Edge-cases and IO failures

Not only can we easily test how our code reacts at certain points in time but the lack of any IO also makes it really easy to test for IO failures and/or weird behaviours!

- What happens if this packets gets dropped and we never receive a response?
- What happens if we get a malformed response?
- What happens if the RTT to the server is really long?
- What happens if we don't have a functional IPv6 interface?
- What happens if we *only* have an IPv6 interface?

By decoupling our protocol implementation from the actual IO side-effects, we are forced go back to the drawing board and design our state machine to be resilient against these problems. Consequently, detecting and dealing with errors simply becomes part of state machine's input handling which leads to more robust code and makes it less likely for edge-cases to only be considered as an after-thought.

## Rust + sans-IO: A match made in heaven?

Rust forces us to declare, which component or function in our code owns a certain value. A common example for these are buffers: When reading from a `UdpSocket`, we need to provide a `&mut [u8]` as a place for the actual bytes being received. Only the owner of a value can declare it mutable and thus either mutate itself or temporarily hand out mutable references to other functions.`UdpSocket` follows this design: It doesn't declare a buffer on its own, instead, it only requires temporary, mutable access to it when it is actually reading from the socket. The explicit modelling of ownership and mutability are integral to how Rust works and what enable features like the borrow-checker.

In a sans-IO design we only have synchronous APIs, i.e. none of the functions on a state machines ever block on IO or time. Instead, they are just data structures.

Those two aspects work exceptionally well together. We can use `&mut` liberally to express state changes and thus leverage the borrow-checker to ensure our code is sound. In comparison, `async` Rust and `&mut` almost feel somewhat at odds with each other.

In Rust, `async` functions are just syntax sugar for a data structure that implements `Future`. Spawning a `Future` into a runtime <sup><a href="https://www.firezone.dev/blog/#user-content-fn-2">4</a></sup> like `tokio` requires this data structure to be `'static` and therefore, it cannot contain any references, including `&mut`. To mutate state that isn't local to the `Future`, you basically have two options:

- Use reference-counted pointers and a mutex, i.e. `Arc<Mutex<T>>`
- Use "actors" and connect them via channels, i.e. spawn multiple tasks with loops that read and write to channels

Both of these options have a runtime overhead: Locks can result in contention and sending messages through channels requires copying. In addition, multiple tasks running inside a runtime operate in a non-deterministic order which can easily lead to race conditions and in the worst case, deadlocks. It appears that with either of these options, we arrive at a design that feels brittle, is prone to deadlocks and no longer employs zero-cost abstractions, yet avoiding all of these is one of the reasons we wanted to use Rust in the first place!

In the sans-IO world, these problems don't exist. Our protocol code doesn't spawn any tasks and thus, `&mut self` is all we need to mutate state. Without tasks or threads, we also don't need synchronisation primitives like `Mutex`. Without channels, there is no need to copy data: The state machine can simply directly reference the buffer we passed to the socket.

Last but not least, we've also found that ever since we moved to sans-IO, our code became much easier to understand. No more tracking down of: Where is the other end of this channel? What if the channel is closed? Which other code is locking this `Mutex`? Instead, it is all just nested state machines and regular function calls.

## The downsides

There are no silver-bullets and sans-IO is no exception to this. Whilst writing your own event loop gives you great control, it can also result in subtle bugs that are initially hard to find.

For example, a bug in the state machine where the value returned from `poll_timeout` is not advanced can lead to a busy-looping behaviour in the event loop.

Also, sequential workflows require more code to be written. In Rust, `async` functions compile down to state machines, with each `.await` point representing a transition to a different state. This makes it easy for developers to write sequential code together with non-blocking IO. Without `async`, we need to write our own state machines for expressing the various steps. How annoying this will be in practise depends on your problem domain. Modelling a request-response protocol is not very difficult as we've seen in the example of a `StunBinding`. On the other hand, if need to express larger, sequential workflows, manually modelling them out as state machines could become tedious.

Finally, the sans-IO design is not particularly wide-spread (yet) in the Rust community. As a result, there are very few libraries out there that follow it. Most of them will either implement blocking or non-blocking IO instead of sans-IO.

## Closing

Writing sans-IO code is unusual at first but really enjoyable once you get the hang of it. In part, this is because Rust provides great tools for modelling state machines. More so, the fact that sans-IO forces you to handle errors as you would any other input simply feels like the way networking code should be written.

That being said, there are additional ways of writing async Rust not discussed in this post. The most notable of those being structured concurrency which sits somewhere "in the middle" between sans-IO and the async Rust portrayed in this post. Read [this article](https://without.boats/blog/let-futures-be-futures/) from withoutboats for more on that topic.

Many thanks to [@algesten](https://github.com/algesten) for providing feedback on drafts of this post.

[^1]: For more details on Firezone's tech stack, see [this article](https://www.firezone.dev/kb/architecture/tech-stack) in our architecture docs.

[^2]: Be sure to implement proper multiplexing of STUN messages at this point. Hint: Use the `TransactionId` and/or the server's address.

[^3]: `boringtun` does call `Instant::now` internally and is thus unfortunately partly impure, see [https://github.com/cloudflare/boringtun/issues/391](https://github.com/cloudflare/boringtun/issues/391).

[^4]: Technically, a thread-per-core runtime could allow non- `'static` `Future` s.