---
title: distributed-systems-trouble
---

Prev: [transactions](transactions.md)
Next: [consistency-and-consensus](consistency-and-consensus.md)

## Faults and Partial Failures

On a normal computer, hardware prioritizes being correct. If there's a
hardware fault, silent failures are fairly rare.

In a distributed system, they're more common. Most of the time, some
parts are broken in some unpredictable way, even if everything else is
working fine. This results in _nondeterminism_, where some things work
and some things don't.

## Cloud Computing and Supercomputing

There's a spectrum of philosophies on how to build large scale computing
systems. Let's focus on Cloud Computing, where a large number of pieces
of commodity hardware are connected.

- They are _online_, where they need to serve users with low latency at
  any time. This forces a requirement of High Availbility. Offline jobs
  do not necessarily have this constraint (like batch jobs).
- Cloud computing uses commodity hardware, which has less redundancy and
  higher failure rates.
- Large datacenters are based on IP and Ethernet, which have less
  reliability and can have exponential backoff times.
- In a system with thousands of nodes, something is almost always
  broken.
- You can restart a node in a redundant system at any time.
- Communication over the internet is generally fairly slow and error
  prone.

### Building a Reliable System from Unreliable Components

Reliable systems can be built from unreliable components.

- Error-correcting codes allow digital data to be transmitted accurately
  across a communication channel that occasionally gets bits wrong.

- TCP over IP ensures that missing packets are retransmitted, duplicates
  are eliminated, and packets are reassembled into the order in which they
  were sent.

## Unreliable Networks

Because we're building _shared-nothing_ systems (the nodes cannot access
each others hard disks)

Internet and Ethernet are asynchronous packet networks -- which can fail
many ways:

1. Your request may be lost (due to an unplugged cable)
2. Your request may be waiting in a queue (too many requests right now)
3. The remote node may have failed (it crashed or powered down)
4. The remote node may have temporarily stopped responding (a long GC
   pause)
5. The remote node may have processed your request, but the response was
   lost on the network
6. The request and response went through, but the network on your
   machine is overloaded and the message may be delivered later

The usual way of handling this is with timeouts, but you don't know if
the remote node got your request.

### Network Faults in Practice

Network partitions are common. It makes sense to deliberately trigger
network problems and test the system's response (like in Chaos Monkey).

## Detecting Faults

Your system needs to take out faulty nodes. However, because networks
are faulty, there's always uncertainty about whether or not a node is
dead or just unreachable.

### Timeouts and Unbounded Delays

The only reliable way to detect a fault is through a timeout. But how
long should it be?

If a node is declared as dead but it isn't, this can cause split brain
problems. If a node is simply unresponsive but labeled as dead, this
cause extra load on the rest of the server.

#### Network congestion and queueing

Packet delays vary mainly due to queueing:

- If several nodes send packets to the same destination, the network
  switch queues them up and feeds them to the destination network link
  one by one. If the queue fills up, the packet is dropped, shedding
  load, but requiring it to be sent again.
- When a packet reaches the destination machine, if all CPU cores are
  busy, the incoming request from the network is queued by the operating
  system until the application can handle it.
- In virtualized environments, an OS is paused for tens of milliseconds
  while another virtual machine uses a CPU core. During this time, the
  VM monitor queues it.
- TCP performs flow control, where a node limits its own rate of sending
  to avoid overloading a network link.

Due to this, it's hard to say what a good timeout is. It can also be
good to set up timeouts with some jitter, where they measure their own
response time and adjust timeouts to how the system is operating.

### Synchronous Versus Asynchronous Networks

Phone calls use a fixed amount of bandwidth, which is allocated for the
call, there is bounded delay and the network does not suffer from
queueing, as there is a fixed 16 bits of space for the call that have
already been allocated.

This differs from asynchronous protocols like the internet -- those are
optimized for _bursty_ traffic. An empty TCP connection has little
overhead, whereas a circuit has fixed overhead. If it does nothing, it
uses up 16 bits. This maximizes utilization at the cost of queueing when
there is some congestion.

## Unreliable Clocks

We need to use time all the time -- like the duration of something, to
determine the state of something, or when something was created/updated.

Computers use a quartz crystal oscillator synchronized over NTP to
adjust its time.

### Time-of-day-clocks

A time of day clock returns the date and time according to a calendar
(like unix time). These are generally synchronized with NTP. They can
have some coarse duration slices, and can move forward and backwards in
time by a remote NTP server.

### Monotonic clocks

Monotonic clocks are always guaranteed to go forwards in time, never
backwards.

NTP may adjust the frequency at which the monotonic clock moves forward
(slewing) if it is going too fast or too slow. This can be up to 0.05%,
but monotonic clocks cannot go backwards.

## Clock Synchronization and Accuracy

- Quartz isn't very accurate - there should be about 17 seconds drift in a
  clock that is resynchronized once a day.

- If a clock differs too much from an NTP server, the local clock will
  be forcibly reset.

- NTP synchronization is only as good as network delay, so roughly 35ms
  over the internet, to about 1s during latency spikes.

- NTP servers can be wrong or misconfigured.

- Leap seconds can result in minutes that are 59 seconds or 61 seconds.
  This can break systems, so NTP servers have been configured to allow
  for smearing, where they are adjusted gradually over the course of a
  day.

- In VMs, the hardware is virtualized, which can create problems for
  applications that require accurate timekeeping.

- Hardware clocks on devices you don't control (on mobile) can be wildly
  incorrect, e.g. to circumvent limits in games.

### Relying on Synchronized Clocks

Using timestamps for causality, while tempting, can be wildly incorrect.
For example, using Last Write Wins, a write that is causally later than
another may be dropped due to skewing on clocks between nodes.

Logical clocks, which are based on incrementing counters rather than
quartz, are a safer alternative for ordering events.

#### Clock readings have a confidence interval

While the machine you're on might produce microsecond or nanosecond
resolution, the best possible accuracy is probably in the tens of ms,
and the error can spike to 100ms in network congestion.

Truetime in spanner gives an exception -- it tells you the [earliest,
latest] tuple pair of timestamps which reports the confidence interval.

Spanner uses this to implement snapshot isolation across datacenters.

## Process Pauses

For leader election, a group of nodes must agree upon a leader. This
requires getting a lease from all the other nodes, and then acting
during that lease. If it doesn't renew its lease, another node can take
over.

This can go wrong in many cases:

- The GC is running, stopping the world for multiple seconds
- In virtualized environments, a VM can be suspended and resumed, where
  its state is written to disk, and then read from disk
- Laptops might be suspended
- a thread running the application/hypervisor might context switch for a
  long time
- asynchronous disk access pauses a thread
- the OS is swapping
- the hardware receives a SIGSTOP or other instruction.

In many cases, the GC can be troublesome, so it can be useful to use a
technique that minimizes its effects.

## Knowledge, Truth, and Lies

### The Truth is Defined by the Majority

Assume that there's an asymmetric fault, where a node is available to
receive messages but not send any. In this case, hopefully the system
deems it dead and elects a new node.

#### The leader and the lock

Frequently, a system requires there to only be one of a thing, like a
leader.

Imagine the case where a leader must only allow one client to access a
file at a time (otherwise there would be data corruption).

Imagine a situation where a client believes it has the lease for a file,
and then receives a stop the world GC pause, where its lease expires. At
that point, the lease is given to another client, who starts writing to
that file, corrupting it.

We need a better way:

#### Fencing tokens

To lock our resource correctly, like above, we need to ensure that the
first client cannot disrupt the entire system, using fencing tokens.

A fencing token is a lease + a number that increases monotonically.

Let's say the client 1 gets a lease + the number 1. It then pauses for a
while, while client 2 gets a lease + the number 2. The second client
sends a write request, which is accepted by the server, and the server
sets its fence to 2. After client 1 tries to send a write, that is
rejected since the server saw a write with a number of 2.

This is basically what the zxid in zookeeper does.

Prev: [transactions](transactions.md)
Next: [consistency-and-consensus](consistency-and-consensus.md)
