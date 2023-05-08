# Design a file storage service

Let's try to design a file storage service:

A bunch of NFS Clients connect to some backend, and then those backends route requests to the physical disks with the blocks.

Using standard file servers is ok for small scale:

But you have to rebalance files between computers when one gets too large, and then you need to shard PB file systems to different computers.

Instead, Oracle FSS uses Paxos to coordinate reads and writes to a computer, called extents.

The state of an extent fits into a single server, and it manages a few GBs of disk. They have a state machine of a few MBs that can be shuffled around during load balancing and failure recovery. They are replicated 5 times.

In order to operate on pages in a distributed fashion, FSS uses Multipage Store Conditional (MPSC), which takes 15 pages, puts them into memory, and grabs a version tag that is guaranteed to change whenever the page is modified for each page.

It then changes the contents of the page in memory, and updates the version tags for updated files.

It then presents the new pages to the MPSC system with tags. If the version numbers all line up, then it succeeds, and can be written atomically. If not, then this operation fails, and the system tries again.
