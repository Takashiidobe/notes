---
title: "Distributed OLTP Database Systems"
pdf: "[[23-distributed-oltp-database-systems.pdf]]"
---

# Distributed OLTP Database Systems

Prev: [[22-introduction-to-distributed-databases]]
Next: [[24-distributed-olap-database-systems]]

## OLTP vs. OLAP

**On-line Transaction Processing (OLTP)**
    - Short lived read/write transactions.
    - Small footprint.
    - Repetitive operations.

**On-line Analytical Processing (OLAP)**
    - Long-running, read-only queries.
    - Complex joins.
    - Exploratory queries

## Distributed Transactions

Distributed transactions accesses data on multiple nodes, while preserving ACID guarantees.

We'll assume that nodes are well-behaved. If the other nodes cannot be trusted, the DBMS has to use a byzantine fault tolerant protocol (blockchain) for transactions.

## Atomic Commit Protocols

- Two Phase Commit (Common)
- Three Phase Commit (Uncommon)
- Paxos (Common)
- Raft (Common)
- ZAB (Common)
- Viewstamped Replication

Prev: [[22-introduction-to-distributed-databases]]
Next: [[24-distributed-olap-database-systems]]
