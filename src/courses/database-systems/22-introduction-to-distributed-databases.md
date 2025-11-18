---
title: "Introduction to Distributed Databases"
---

# Introduction to Distributed Databases

Prev: [crash-recovery-algorithms](crash-recovery-algorithms.md)
Next: [distributed-oltp-database-systems](distributed-oltp-database-systems.md)

## Distributed DBMSs

We can use the building blocks that make consistent single-node DBMSses to make distributed database systems. One key point is to make them fault tolerant, where one node failing does not take down the whole system.

Differences between **parallel** and **distributed** DBMSs:

**Parallel Databases**:

- Nodes are physically close to each other.
- Nodes are connected via high-speed LAN (fast + reliable)
- Communication cost between nodes is small.

**Distributed Databases**:

- Nodes can be far away from each other.
- Nodes are connected via a public network, which is slow, unreliable, and can have unbounded response times.
- Coordination is expensive, nodes can crash, packets can get dropped, or never sent to the right location.

## System Architectures

A DBMS's system is concerned with shared resources directly accessible to CPUs.
A Single-node DBMS has a shared everything architecture, where it owns its own local memory and disk.

### Shared Memory

CPUs have access to common memory address space via a fast interconnect. CPUs share the same disk as well. Each DBMS instance on a processor has to know about all the other instances

### Shared Disk

All CPUs can read and write to a single logical disk directly via interconnect, but each have private memory. This is common in cloud-based DBMSs.

The DBMS's execution layer can scale independently from the storage layer. Adding new storage nodes or execution nodes does not affect the layout or location of data in the other layer.

Nodes must send messages between them to learn about the node's current state.

Nodes have their own buffer pool and are stateless. A node crash does not affect the state of the database since that is stored separately on shared disk. The storage disk persists state in case of crashes.

### Shared Nothing

Each node has its own CPU, memory, and disk. Nodes only communicate with each other via network.

These nodes don't share anything, so they must communicate solely over the network. Thus, it is hard to add either more compute or storage, since that requires redistributing data from the other nodes in the cluster, which can be difficult to achieve consensus over. All nodes must also participate in consensus, which is expensive. However, these DBMS's can achieve better performance, and can scale more than other types of distributed DBMS architectures.

## Design Issues

Some questions naturally result:

- How does the application get data?
- How are queries executed on distributed databases? Is the query pushed to where the data is located?
- Should the data be pooled into a common location to execute?
- How does the DBMS ensure correctness?

As well, the hardware matters:

Is it **Homogeneous** where every node is on similar hardware, so each cluster can perform the same set of tasks? This lends itself to a shared nothing architecture, where provisioning and failover are easier.

Is it **Heterogeneous** where nodes have different capabilities? Communication must occur between nodes to carry out a task. A single physical node can host multiple virtual node types for dedicated tasks, and they can scale independently from one node to the other.

## Partitioning Schemes

To increase capacity of the database, we can split the database across disk, nodes, and processors. This is called **sharding** sometimes. The DBMS runs query fragments on each partition and then combines the results to produce a single answer. Users should not need to know where the data is physically located, and how/if the tables are partitioned or replicated. An SQL query that works on a single-node DBMS should work the same on a distributed DBMS.

A partitioning scheme should maximize single-node transactions. This allows the DBMS to avoid coordination overhead, which is more efficient and less error prone.

For **logically partitioned nodes**, particular nodes are in charge of accessing specific tuples from shared disk. For **physically partitioned nodes**, each shared nothing node reads and updates tuples it contains on its local disk.

### Implementation

**Naive Table Partitioning**: Each node stores one table. Each query is routed to a specific partition that uses that table. If query load is equally distributed between tables, this works well, and avoids coordination overhead. If there are a lot of joins or hot tables, then this scales poorly.

**Horizontal Partitioning**: Split a table's tuples into disjoint sets. Then, choose a column that divides the database equally in size, load, or usage. This is called the partition key. The DBMS can partition a database physically (shared nothing) or logically (shared disk) via hash partitioning or range partitioning.

## Distributed Concurrency Control

The DBMS needs a way to support distributed transactions. Some ways are:

- **Coordinator**: There is a global coordinator. The client communicates with the coordinator to acquire locks on partitions that the client wants to access. Once it receives acknowlegement from the coordinator, the client sends its query to those partitions.
Once the query is done, the client sends a commit request to the coordinator. The Coordinator then verifies to make sure that transaction is allowed to commit.

- **Decentralized**: Nodes organize themselves. The client directly sends queries to one of the partitions. The home partition will send results back to the client. The home partition is in charge of communicating with other partitions and committing. Decentralized approaches have a hard time with distributed locking, however.

Prev: [crash-recovery-algorithms](crash-recovery-algorithms.md)
Next: [distributed-oltp-database-systems](distributed-oltp-database-systems.md)
