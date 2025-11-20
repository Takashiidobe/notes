---
title: "Cloud Replicated Db, Aurora"
lecture: "[[09-distributed-transactions-lecture]]"
---

# Cloud Replicated Db, Aurora

Prev: [[09-more-replication-craq]]
Next: [[11-cache-consistency-frangipani]]

Aurora is AWS' high performance database. To explain its design choices,
let's talk about EC2.

At first, AWS offered EC2, which is a VM service. Each VM would require
some amount of storage, which it had on the computer. This works fine in
most cases, but if the EC2 instance ever goes down, the state it saves
on disk also becomes unreachable. If you're running a DB instance on an
EC2 instance, then your database becomes unreachable. Not very good.

To improve this, AWS offered EBS (Elastic Block Service) which could be
mounted by an EC2 instance. EBS replaced the hard disk of an EC2
instance with a hard disk on another computer, and replicated storage
between two disks. Thus, if one disk became unreliable, another disk
could service reads and writes.

But that wasn't enough, since it's possible either the EC2 instance or
the EBS instance could fail, and a database would be useless if either
of them failed. As well, writes would be slow because of the
replication. Also, customers really wanted the ability to have their
database across Availability Zones (AZs) which this setup could not do.

So AWS released RDS (Relational Database Service). RDS was a modified
version of MySQL that would replicate its writes to 6 times to 3 AZs
with 2 copies of the data. However, this was ill-performant because
actually committing the data on disk required page-writes, and pages
were generally 8KB. Thus, every write was sending 8KB of data over the
wire, making it very slow in practice.

AWS released Aurora to deal with this. Aurora only replicates the
write-ahead log (WAL) for a write, 6 times to 3 AZs. Since each WAL
write is 1-100 bytes or so, this is much faster.

This allows Aurora to still keep writing when one AZ is down, and read
when one AZ + one server is down. Aurora does this by adding a version
number to each write. On read, even if the read cluster may not pick the
"latest" write, the highest version number is chosen, indicating the
most recent write.

Aurora also has:
- incremental increases in hard disk storage (in blocks of 10GB),
- Fault tolerance by quickly standing up a new shard by using the WALs
- Has fast latencies, since it receives fast reads
- Distributes load well, since data is naturally well sharded.

Prev: [[09-more-replication-craq]]
Next: [[11-cache-consistency-frangipani]]
