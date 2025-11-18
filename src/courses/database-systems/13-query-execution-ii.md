---
title: "Query Execution II"
---

# Query Execution II

Prev: [query-execution-i](query-execution-i.md)
Next: [query-planning--optimization-i](query-planning--optimization-i.md)

## Background

The DBMS wants to support parallel queries for a few reasons, but mainly performance and availability related. However, parallel DBMS' and distributed DBMS' differ slightly in their characteristics.

**Parallel DBMS**:
- Nodes are close to each other
- Nodes are connected with fast and reliable LAN.

**Distributed DBMS**:
- Nodes can be far from each other
- Nodes are connected with slow and unreliable networks.

**Types of Parallelism**:
- **Inter-Query**: The DBMS executes different queries concurrently
- **Intra-Query**: The DBMS executes the operations of a single query in parallel

## Process Models

The DBMS process model defines how the system supports concurrent requests for multiple users. The DBMS has one or more workers that are responsible for executing tasks.

**Process per Worker**:
- Each worker is a separate OS process that relies on the OS scheduler
- Uses shared memory for global data structures
- A process crash does not take down the system

**Process Pool**:
- A worker uses any process free in the pool
- Relies on the OS scheduler and shared memory
- Can have bad cache locality due to no guarantee of using the same process

**Thread per Worker**:
- Single process with multiple worker threads
- DBMS has to manage its own scheduling
- A thread crash can kill the entire system

## Inter-Query Parallelism

The DBMS allows multiple queries to execute simultaneously. More detail in Concurrency Control protocols.

## Intra-Query Parallelism

The DBMS runs a single query faster by splitting up its work in parallel. To do this, the DBMS decomposes the query plan and data set into independent chunks and then coalesces the result later.

The DBMS inserts an **exchange** operator into the query plan to aggregate results. There are three types of exchange operators:

1. **Gather**: Combine the results from multiple workers into a single output stream.
2. **Repartition**: Reorganize multiple input streams across multiple output streams. The DBMS can redistribute inputs however it likes.
3. **Distribute**: Split a single input stream into multiple output streams.

**Inter-Operator Parallelism**
- The DBMS overlaps operators to pipeline data from one stage to the next without materialization.

This is useful for stream processing systems, since materialization is expensive for those systems.

**Bushy Parallelism**
- Inter-operator parallelism, where workers execute multiple operators from different segments of the query plan at the same time.

## I/O Parallelism

Using additional processes/threads to execute queries in parallel will not improve performance if I/O is the bottleneck. Thus, it's important to split up the database across multiple storage devices.

**Multi-Disk Parallelism**
One can configure the OS/Hardware to store the DBMS' files across multiple storage devices. It can be done with RAID as well.

**File-based Partitioning**
The DBMS can write to multiple files instead of 1, to reduce contention. Log files are most likely shared, however.

**Logical Partitioning**
Split a single logical table into disjoint physical segments that are stored/managed separately.

**Verticial Partitioning**
- Store a table's attributes in a separate location.
- Store tuple information to reconstruct the original record.

**Horizontal Partitioning**
- Divide the tuples of a table into disjoint segments based on partitioning keys

Prev: [query-execution-i](query-execution-i.md)
Next: [query-planning--optimization-i](query-planning--optimization-i.md)
