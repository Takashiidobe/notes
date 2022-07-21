---
title: "Direct Links"
---

# Direct Links

Prev: [foundation](foundation.md)
Next: [internetworking](internetworking.md)

## Problem: Connecting to a Network

In chapter 1, setting up a network was discussed, but not connecting to
a node to the network, like through copper, fiber, or through radio
waves.

Five problems emerge after connecting two nodes, and before exchanging
packets:

1. Encoding bits onto the transmission medium to be understood by the
   receiving node
2. Delineating bits over to the link that are delivered to the end node
3. Detecting errors due to corrupt bits
4. Making a link appear reliable even though it is unreliable
5. Controlling access to the node (security)

### Technology Landscape

Today's internet involves a disparate amount of clients (desktops,
laptops, phones, mainframes) connecting to routers which are then
connected by the ISP to the rest of the internet.

These links may be copper, fiber, radio waves, or something else, but
they should all appear to the user to have the same interface.

One important characteristic of the physical medium is the frequency, in
hertz, that a wave oscillates. Copper might have a wavelength of 6.67e5
meters.

Binary could be sent by encoding a high-signal (for 1) or a low-signal
in the physical medium.

There's a lot of last-mile connections to the home:

| Service         | Bandwidth      |
|-----------------|----------------|
| DSL (copper)    | up to 100 Mbps |
| G.Fast (copper) | up to 1 Gbps   |
| PON (optical)   | up to 10Gbps   |

Or a mobile network, like 5G.

There's also backbone links to connect cities, normally with fiber,
using SONET (Synchronous Optical Network).

## Encoding

The job of encoding is done by a network adaptor, a piece of hardware
that connects a node to a link. This handles encoding and decoding at
each node.

The first algorithm is called `non-return to zero`, (NRZ), which maps a
high-signal to 1 and a low-signal to 0.

This has a few problems:

The receiver decodes bits using an average. If it does so, then sending
a set of 0 or 1 skews the average over time, leading to `baseline
wander`, making the receiver mistake 0 and 1.

Another problem is the clocks of the sender and receiver need to be in
sync for them to understand the boundary between a high and low signal.
If the signal changes (0 -> 1) or (1 -> 0) then the receiver can
synchronize its clock and verify which signal is which. The clock will
skew if bits aren't flipped every once in a while.

An alternative approach, `non-return to zero inverted` (NRZI) encodes a
transition from the current signal to signal a 1, and staying at the
current signal to be a 0. This solves the problem for consecutive 1, but
not consecutive 0.

Another algorithm, the Manchester encoding stream, has 0 being a
low-to-high transition, and a 1 as a high-to-low transition.

This works, but it doubles the rate at which transitions are made on the
link, which means the receiver has half the time to detect eachpulse fo
the signal, the `baud rate`. This has a 50% efficiency compared to `NRZ`
and `NRZI`.

Another encoding is called `4B/5B`, which takes 4-bits of data and turns
them into a 5-bit code. This involves sending bits in a way that there
is no more than one leading zero and no more than two trailing zeroes.
This is then transmitted with the NRZI encoding, which results in 80%
efficiency.

## Framing

Framing constitutes the problem of cutting up bits into a sets of
meaning.

### Byte-Oriented Protocols (PPP)

Byte-Oriented Protocols frame each collection of bits as characters.
This involves using sentinel characters to signal the beginning and end
of the frames to delimit them: `STX` for start and `ETX` for the end.
Characters can be escaped with the `DLE` character.

The alternative is to send the number of bytes in the frame at the
beginning of the frame. However, a transmission error could corrupt the
count field, which would lead to dropped frames.

The Point-to-Point Protocol (PPP) uses sentinels and character stuffing
looks like this:

| 8    | 8       | 8       | 16       |         | 16       | 8    |
|------|---------|---------|----------|---------|----------|------|
| Flag | Address | Control | Protocol | Payload | Checksum | Flag |

The start-of-text character is denoted as the Flag, `01111110`.
The Address and Control fields are defaulted.
The Protocol identifies the high-level protocol, like IP.
The Payload size is 1500 bytes, but can be negotiated.
The checksum is a CRC (cyclical redundancy check).
The Final flag is for the end of frame character.

The PPP format also uses a protocol called Link Control Protocol (LCP)
to negotiate the sizes of certain frames (like the Checksum and
Payload).

### Bit-Oriented Protocols (HDLC)

A Bit-Oriented protocol like High-Level Data Link Control (HDLC) views a
frame as a collection of bits.

| 8     | 16     |      | 16  | 8   |
|-------|--------|------|-----|-----|
| Begin | Header | Body | CRC | End |

The beginning and end of a frame is signaled with `01111110`, and also
sent when the link is idle so the receiver can synchronize with the
sender.

Bit stuffing works like so: any time five consecutive ones have been
transmitted, the sender inserts a 0 before the next bit.

The receiver then has two choices: if it sees five ones and one zero,
then it can discard that one.
If it sees another 1, then it looks at the next bit. If the next bit
is a 0, then it is the end of frame marker, if it sees another 1, this
is an error, and it discards the whole frame.

### Clock-Based Framing (SONET)

A Clock-Based Framing protocol like Synchronous Optical Network (SONET)
is used mainly for fiber.

SONET is used to merge large numbers of 64-kbps telephone line channels
to a high-speed link.

SONET uses 2 bytes for the header, and arranges bytes as 9 rows of 90
bytes each. The delimiting bit pattern should appear every 810 bytes,
since that is how long a frame is in SONET.

SONET also uses NRZ with an XOR for the overhead 3 bytes.

Because this is used to merge multiple lower-speed lines into one, SONET
uses `STS`, which involves combining a multiple of `STS` frames into one
`STS-N` frame by interleaving them into one larger frame.

## Error Detection

Sometimes bit errors are introduced into frames. There are two parts of
the problem: detection and correction.

You could leave correction to simply ask the client to send the payload
again, but this requires the link to be relatively error free.

The basic idea behind error detection is to add redundant information to
a frame to determine if errors have been introduced. Imagine sending two
copies of the data. If they're both identical, it's most likely ok, but
the same bit could've gotten corrupt, and the receiver wouldn't know.
This costs 2n data as well.

CRC does better - with a frame carrying 1500 bytes, a 32-bit CRC will
catch most errors.

### Internet Checksum algorithm

The internet checksum algorithm involves adding up all the words being
transmitted, and transmitting the result of the ones complement of the sum.

```c
uint8_t cksum(uint8_t *buf, int count) {
    uint16_t sum = 0;

    while (count--) {
        sum += *buf++;
        if (sum & 0xFFFF0000) {
            /* carry occurred, so wrap around */
            sum &= 0xFFFF;
            sum++;
        }
    }
    return ~(sum & 0xFFFF);
}
```

This algorithm is compact (16 bits) but isn't great for error detection
-- if the same number of bits are incremented as they are decremented,
no error would be caught.

### Cyclic Redundancy Check

The CRC uses polynomial mathematics to improve error detection:

Imagine representing `10011010` as an n-th degree polynomial. Each bit
that is set is the polynomial.

`x^7  + x^4 + x^3 + x`.

This is called M(x).

Ethernet uses a polynomial of degree 32 to calculate a divisor
polynomial, C(x).

Next, to send the message, the sender sends M(x) and the redundant k
bits, which is P(x).

If there are no errors, then P(x) should be divisible by C(x) exactly,
with no remainder. If so, this is ok. If not, there was an error.

This can be done quickly using bitwise operations, but can also be shown
with these three lemmas:

1. Any polynomial B(x) can be divided by a divisor polynomial C(x) if
   B(x) is of a higher degree than C(x).
2. Any polynomial B(x) can be divided once by a divisor polynomial C(x)
   if B(x) is of the same degree as C(x).
3. The remainder obtained when B(x) is divided by C(x) is obtained by
   performing the XOR operation on each pair of matching coefficients.

For example, 1101 / 1001 would leave a remainder of 0100. We can easily
see that in decimal (13 % 9 = 4).

To divide the transmitted message:

1. Multiply M(x) by x^k, we add k zeros at the end of the message. This
   is T(x).
2. Divide T(x) by C(x) and find the remainder.
3. Subtract the remainder from T(x).

A C(x) with the following properties can address the following:

| error                  | property                         |
|------------------------|----------------------------------|
| single-bit             | x^k and x^0 are set              |
| double-bit             | C(x) has a factor of three terms |
| odd number errors      | C(x) contains factor (x + 1)     |
| burst error `<` k bits | burst is `<` k bits              |

It seems like correction is always better than just detection, but
correction requires a larger number of bits than purely detection, and
this must be sent all the time, so everything gets a larger overhead.

## Reliable Transmission

Reliability is generally provided at the transport level, even though it
could be provided at the link-level. It has some overhead, but is
required generally deferred to the transport level.

Reliable delivery is usually accomplished with acknowledgements and
timeouts. The sender would send a packet, and then wait for a response
from the receiver, who would send back an ACK. If the response is not
received before the timeout expires, it is sent again by the client.

### Stop-and-Wait

The simplest Automatic repeat request (ARQ) is Stop-and-wait. The sender
sends a packet, then waits until the timeout before resending, otherwise
moving onto the next packet.

This has the problem where if the ACK from the receiver is lost, the
sender will send a duplicate packet, which the receiver wouldn't be able
to distinguish.

To prevent this case from happening, the sender can mark even and odd
packets by using a single bit -- the first frame would be 0, the second
would be 1, the third would be 0 again. This correctly works as long as
there is only 1 outstanding frame over the wire, which can be slow:

Imagine a 1.5 Mbps link with 45-ms round trip time. Since only one
packet can be sent at a time, assuming 1KB frames:

`Bits-Per-Frame / Time-Per-Frame = 1024 x 8 / 0.045 = 182 kbps`

We'd only be using about 1/8 of the link's capacity.

### Sliding Window

To be able to send more than one frame at a time, we can use a sliding
window algorithm. We send a set of frames, and as the receiver
acknowledges frames inside the set, we can send more frames.

### Finite Sequence Numbers and Sliding Window

We made a simplifying assumption above -- that we could have integers
with no wrap around infinitely incrementing. That never happens in
practice, since we don't have infinite bandwidth. We need a byte space
twice as big as the amount of bytes we can send at a time, otherwise our
wrap-around will make it impossible to distinguish between bits.

### Frame Order and Flow Control

The Sliding Window Algorithm provides the following roles:

1. Reliably delivering frames on an unreliable link.
2. Preserving Order of frames
3. Throttling of sender

### Concurrent Logical Channels

ARPANET didn't use the sliding window protocol, rather a stop-and-wait
algorithm over many links (basically many queues).

## Multi-Access Networks

Multi-access networks are dominated by Ethernet, a point to point wired
protocol.

### Physical Properties

Ethernet was originally implemented with coaxial cable of up to 500m, in
twisted copper pairs. Nowadays it can have fiber.

Ethernet only allowed for four repeaters, a device that forwards
digital signals, which allowed for a maximum reach of 2500m. Any signal
placed on the Ethernet by a host is broadcast over the entire network.

### Access Protocol

The frame format of Ethernet is defined below:

| 64       | 48        | 48       | 16   |      | 32  |
|----------|-----------|----------|------|------|-----|
| Preamble | Dest addr | src addr | type | body | CRC |

The preamble allows for synchronization between sender and receiver.
The destination address is a unique 48-bit address for every ethernet
cable.

### Addresses

Each host on Ethernet has a unique 48-bit address. Every manufacturer
gets a 24-bit prefix that is prepended to the address of every adaptor
built.

It might look like `8:0:2b:e4:b1:2`, which is the human-readable
representation of `00001000  00000000  00101011  11100100  10110001
00000010`.

### Transmitter Algorithm

The algorithm is simple for receivers. For senders:

If an adaptor has the line, it sends a frame immediately. Since it can
only send 1500 bytes, it won't take up that much space.

If the line is busy, it waits for the line to become idle, then
transmits.

If two or more nodes are competing for the line, they might choose to
defer (since there is no centralized control), allowing other nodes to
use the line.

If two adaptors send a frame at the same time, there's a collision, and
then the two adaptors transmit a 32-bit jamming sequence, and stop the
transmission.

Prev: [foundation](foundation.md)
Next: [internetworking](internetworking.md)
