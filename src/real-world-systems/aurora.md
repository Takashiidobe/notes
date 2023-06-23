---
title: "AWS Aurora"
---

# How does Aurora Work?

Aurora improves a traditional database by distributing the storage backend. It replicates WALs to remote storage, and employs a primary-replica setup. By default, aurora replicates the data 6 times in 3 different data centers.
This is expensive, so it only requires a quorum to acknowledge writes (4 out of 6).
It also only does reads from one replica.

The primary instance serves both read and write requests. The followers replay the WAL entries to their copy of the database, and only serve reads.
If they receive a read for an item that has been updated by the leader, they send the read request to the follower.
As well, it will issue a read request from the leader to fetch the page that isn't present in its buffer so it will be ready for next time.

- Replication lag is about 10ms
