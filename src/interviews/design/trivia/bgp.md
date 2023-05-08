# What is BGP? How does it work?

BGP (Border Gateway Protocol) is the postal service of the internet.

When a packet is sent, it has a source and a destination -- BGP finds the shortest path to its destination, and routes the packet there.

It uses Open Shortest Path First (OSPF) to route packets, and goes through ASes (Autonomous System)s which then route packets to their destination.

ASes are generally run by ISPs.

Unfortunately, BGP can be problematic, as it operates on trust. If one ISP advertises misinformation, then it can make sites unaccessible for the entire internet.
