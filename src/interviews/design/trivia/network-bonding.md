# Network Bonding

Network Bonding/NIC Teaming is a way to increase redundancy by connecting multiple network interfaces into a single interface. It improves performance and redundancy by increasing throughput and bandwidth.

Some of the network bonding modes in linux involve:

- Mode-0 (balance-rr): It is the default mode and is based on round-robin policy. It offers features like fault tolerance and load balancing. 
- Mode-1 (active-backup): It is based on an active-backup policy. In this, only one node responds or works at the time of failure of other nodes. 
- Mode-2 (balance-xor): It sets an XOR (exclusive-or) mode for providing load balancing and fault tolerance.
- Mode-3 (broadcast): It is based on broadcast policy. It sets a broadcast mode for providing fault tolerance and can be used only for specific purposes.
- Mode-4 (802.3ad): It is based on IEEE 802.3ad standard also known as Dynamic Link Aggregation mode. It sets an IEEE 802.3ad dynamic link aggregation mode and creates aggregation groups that share the same speed and duplex settings. 
- Mode-5 (balance-tlb): It is also known as Adaptive TLB (Transmit Load Balancing). It sets TLB mode for fault tolerance and load balancing. In this mode, traffic will be loaded based on each slave of the network.
- Mode-6 (balance-alb): It is also known as Adaptive Load Balancing. It sets ALB mode for fault tolerance and load balancing. It doesn’t need any special switch support.
