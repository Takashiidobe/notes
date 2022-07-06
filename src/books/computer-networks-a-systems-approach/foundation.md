---
title: "Foundation"
---

# Foundation

Next: [direct-links](direct-links.md)

## Problem: Building a Network

To build a network that has the capability to scale to a global
audience, and support apps like teleconferencing, video on demand,
e-commerce, distributed computing, and digital libraries, what
foundational technology should be supported?

It used to be that networks were specialized for one kind of job --
sending voice over telephone lines, or cable TV to homes. Basically,
they use specialized hardware to send specific data to specific
hardware.

Computer networks are meant to be general purpose -- they use
general-purpose hardware to send general-purpose data to other
general-purpose hardware.

It is important to learn about network protocols that came before, as
well as the architecture, performance, metrics of networks.

### Applications

There are a few groups of people who use the internet:

1. Users
2. Application developers
3. Network managers
4. Network designers

### Classes of Applications

The web is the most popular networked app, and HTTP is the most
popular protocol:

For example, querying `http://www.cs.princeton.edu/~llp/index.html`
means to use the HTTP protocol to download the page, with
`www.cs.princeton.edu` meaning to go to the machine that acts as this
address, and find the page `~/llp/index.html` on the machine that serves
it, and download it.

DNS turns `www.cs.princeton.edu` into its IP address `128.112.136.35`,
three messages to set up a TCP connection, four messages to send the GET
requests between request and server, and four messages to tear down the
TCP connection.

Other applications use streaming -- like VODs or social media, to watch
images and video. It would be bad if an entire video file was required
to be downloaded before watching the first scene (imagine having to wait
hours to download a movie before getting started).

Streaming requires that the server promptly sends messages to the
receiver, and the receiver promptly uses this messages on arrival.

In streaming applications audio and video streams are consumed in a
continuous and in-order fashion. Skipped sounds/frames are not
acceptable, but they might be for a web page, where a part of it might
not render.

In real-time audio and video applications, like Voice-over-IP apps,
performance is far more critical and must be supported bidirectionally.
300 ms is a reasonable upper bound before conversations become hard to
execute, and 100 ms is totally fine for most people.

These applications show the diversity of applications and the necessity
of flexibility for networking protocols to build for the web.

### Requirements

Let's discuss some previously created computer networks from the ground
up to learn more about these choices.

### Stakeholders

This book is written for three kinds of people:

1. Application programmers, who write applications that care about
   messages being sent promptly with few errors
2. Network operators, who care about ease of administration and
   management of networks
3. Network designers, who care for efficient use of network resources,
   and that they are fairly distributed.

### Scalable Connectivity

The internet is built to scale to every computer in the world -- it
scales because it can serve an arbitrary amount of computers.

Computers, also called `nodes` are connected by `links` to each other.
Networks can be point-to-point (where the computers are directly
connected to each other through a link, or multiple-access, where
computers are connected to a device that can connect to other devices.

Multiple-access is generally used for `last-mile` connectivity, since it
is limited in size.

Fortunately, computers don't have to be directly connected to each
other to connect to the internet. A switched network (like circuit
switching for telephones and packet switching for the internet) allow
for nodes to be forwarded to each other.

This is done by `store-and-forward`ing packets. A router would receive a
packet from a sender, store it in memory, and then send it across the
network to the next node.

These nodes are commonly called `switches`, and denoted with clouds.
Likewise, a node that connects two or more networks is called a
`router`, and this is what forms the basis of the internet.

Finally, nodes must be able to connect to other nodes, and thus be
uniquely identified. IP addresses are used for this, and the process of
connecting disparate computers is called `routing`.

The node must be able to `unicast` (send a message to one node only) and
`multicast` (send a message to multiple nodes).

### Cost-Effective Resource Sharing

Packet switching is chosen for its efficiency in sending messages from
one set of nodes to another. This is done with `multiplexing`, which is
analogous to job sharing in operating systems.

S1                          R1
  \                       /
S2 - Switch 1 -> Switch 2 - R2
  /                       \
S3                          R3

One algorithm is synchronous time-division multiplexing (STDM) which is
basically round robin.

Another is frequency division multiplexing (FDM), where each job is
transmitted at a different frequency.

The queueing algorithm that the internet uses is Statistical
multiplexing, where data is transmitted on demand, so there is no
wastage. As well, there is a limit of block-size that a flow can send
data (a packet). After a packet is assembled, it is sent, and the next
job is processed.

The receiving switch then receives the packets all at once, and then
directs them to the right location. There might be `congestion` when one
switch sends messages faster than the receiver can process them, leading
to `dropped packets`.

### Support for Common Services

Networks provide channels for applications to talk to each other in an
abstract fashion.

They might support sending files (like FTP or NFS) in a request/reply
format.

Or they might want to support a message stream in a request/reply or
peer to peer format.

Or video on demand or videoconferencing applications, which support
one-way and two-way real time traffic.

There's also a question of how complicated the underlying protocols
should be, and how much power they should give to the user.

### Reliable Message Delivery

Reliable message delivery is one of the most important functions of a
network. Networks are unreliable, however. Computers fail, links fail,
buffer space runs out, etc.

Three types of failures:

1. Bit errors are introduced into the data. (This is rare, about
   1e12-1e14 on fiber)
2. Packets can be dropped (congestion, or uncorrectable bit flipping)
3. The computers or links used crash

### Manageability

A final important requirement is that networks must be managed. Features
need to be balanced with bugs and maintainability.

## Architecture

A computer network must provide general, cost-effective, fair, robust
connectivity, but the requirements and applications that run on top of
them change as well.

### Layering and Protocols

Abstraction is a useful tool in reducing the complexity of an object by
making a distinction between its public interface and its
implementation.

Networks do the same with layering, where a protocol consumes the public
interface of a layer below it, and surfaces its own interface with
different characteristics than the one below it.

Layering might not be strictly linear: there might be multiple
abstractions at certain levels.

```
| Application Programs      |
| Req/Res | Message stream  |
| Host to Host connectivity |
|     Hardware              |
```

We will call these layers `protocols` which have two parts:

A service interface, which defines how to use the protocol
A peer interface, which defines how other machines would call it.

A protocol might use transport defined on a lower level, which is then
decoded by a peer interface and used there.

### Encapsulation

Data in higher-level protocols is embedded in lower-level protocols by
adding a `header` or a `trailer` with the information.

As well, higher-level peer applications won't see the lower-level
protocol information, as that has been removed and processed by
lower-level protocol applications.

### Multiplexing and Demultiplexing

Since the internet sends multiple messages to be processed at the destination, there needs to be some way to identify messages. This is called a `demultiplexing key` or a `demux` key.

### OSI Model

The OSI coined a 7-layer protocol graph:

Application -> Presentation -> Session -> Transport -> Network -> Data
link -> Physical

- The physical layer (copper/fiber) handles sending bits and bytes through
a physical medium.
- The data link collects these bits into a collection called a `frame`.
  This is processed by a network adaptor.
- The network layer handles routing with packet switching.
- The transport layer handles messages on higher levels.
- The session layer ties together the disparate transport streams
- The presentation layer contains types and data
- The application layer handles protocols like HTTP.

### Internet Architecture

The internet architecture might look like this:

```
| Application |
| TCP | UDP   |
|      IP     |
| Subnetworks |
```

Application protocols would include HTTP, FTP, which run over TCP/IP,
and DNS, which runs over UDP/IP.

Protocols can be added to the Internet architecture by the IETF as long
as there is a strict protocol and at least one representative
implementation.

## Software

The runaway success of the internet can be attributed to the fact that
it runs on general purpose hardware. New functionality can be added with
just a small bit of programming.

General purpose hardware is also now able to do interesting things like
play back audio and video at speed and resolution that allows for apps.

### Socket API

The Socket API is the interface exported by the network, and implemented
by the OS.

The building block of the socket API is the socket:

```c
int socket(int domain, int type, int protocol);
```

The `domain` argument specifies the domain used.  `PF_INET` for the
internet, `PF_LOCAL/PF_UNIX` for Unix, and `PF_PACKET` for the network
interface (not TCP/IP).

The `type` argument can be `SOCK_STREAM` for a bidirection byte stream
(TCP), `SOCK_DGRAM` for a message-oriented service (UDP), or `SOCK_RAW`,
which provides direct access to the hardware (requires root).

The `protocol` argument defines the protocol used, like
`AF_UNIX/AF_LOCAL`, `AF_INET` for IPv4, `AF_INET6` for IPv6,
`AF_BLUETOOTH` for bluetooth, or `AF_RDS` for reliable datagram sockets.
You can pass `UNSPEC`, which lets the `socket` call choose.

The call to `socket` returns an `int`, which is a handle to the socket.

For servers, the server can open a connection with `bind`, `listen`, and
`accept`.

```c
int bind(int socket, struct sockaddr *address, int addr_len);
int listen(int socket, int backlog);
int accept(int socket, struct sockaddr *address, int *addr_len);
```

`bind` binds the socket to a specified address. For internet protocols,
this requires the IP address and the port number.

`listen` defines the number of connections that can be pending on the
socket.

`accept` opens connection and embeds the remote participants address to
the `struct sockaddr *address`.

For clients, we use `connect`:

```c
int connect(int socket, struct sockaddr *address, int addr_len);
```

Which establishes a connection and returns when the application can send
data. The client normally chooses a random unused port to send the data.

Then, the `send` and `recv` calls allow the client to send data:

```c
int send(int socket, char *message, int msg_len, int flags);
int recv(int socket, char *buffer, int buf_len, int flags);
```

`send` sends data over the socket, and `recv` receives data from the
socket into the selected buffer.

## Performance

### Bandwidth and Latency

Network performance is measured in bandwidth and latency. Bandwidth is
how many data per time unit the connection can send. Throughput is the
measured performance of the system -- the actual amount of bits that can
be sent over the network in practice.

Latency corresponds to how long it takes for a message to travel from
one node to another. It takes 24 ms to go from one coast of North America
to another.

Latency can be calculated like so:

Distance is the length of the wire, and speed of light is the effective
speed of light over that medium -- light travels at 3e8 m/s in a
vacuum, 2.3e8 m/s in a copper cable, and 2e8 m/s over fiber.

```
Latency = Propagation + Transmit + Queue
Propagation =  Distance/SpeedOfLight
Transmit = Size/Bandwidth
```

There is some queueing and transmitting delays that occur over networks,
so those are accounted for as well.

| Link Type           | Bandwidth | One-Way Distance | RTT     | RTT x Bandwidth |
|---------------------|-----------|------------------|---------|-----------------|
| Wireless LAN        | 54 Mbps   | 50 m             | 0.33 μs | 18 bits         |
| Satellite           | 1 Gbps    | 35,000 km        | 230 ms  | 230 Mb          |
| Cross-country fiber | 10 Gbps   | 4,000 km         | 40 ms   | 400 Mb          |

### High-Speed Networks

High-speed networks are now a reality, but are dominated by the costs of
setting up a connection:

Imagine a 1 MB file being sent cross-country, for a 100-ms RTT, over a
1Gbps link.

The effective throughput would be:

```
Throughput = TransferSize / TransferTime
TransferTime = RTT + 1/Bandwidth x TransferSize
1 MB / 108 ms = 74.1 Mbps
```

So our 1 Gbps link has an effective throughput of 74.1 Mbps.

### Application Requirements

Some applications need to state an upper limit on their bandwidth usage:

Imagine painting a TV screen of 352x240 with 24-bit color at 30fps.
Every frame would require (352 * 240 * 24 / 8) or ~250 KB of data, which
is about 75 Mbps.

The upper limit the application needs is 75Mbps, it needs no more.

However, it is possible to compress video since most of the colors of
the frames are the same, since little changes frame to frame in a video.

Thus, we have to know the average bandwidth required (which could be
2Mbps, if we only send diffs along) and the peak, which could be 75Mbps
for a short burst.

The receiver of the bits can buffer (store the bits in-memory) but might
drop data if the buffer is filled up. So, it's important to know the
jitter for a network -- the amount of variation in time between packets
being sent.

Next: [direct-links](direct-links.md)
