---
title: Snowflake
author:
  - "Abdul Q. Munir"
  - "Allison W. Lee"
  - "Artin Avanes"
  - "Ashish Motivala"
  - "Benoit Dageville"
  - "Daniel Engovatov"
  - "Greg Rahn"
  - "Jiansheng Huang"
  - "Jon Bock"
  - "Jonathan Claybaugh"
  - "Marcin Zukowski"
  - "Martin Hentschel"
  - "Peter Povinec"
  - "Philipp Unterbrunner"
  - "Spyridon Triantafyllis"
  - "Steven Pelley"
  - "Thierry Cruanes"
  - "Vadim Antonov"
doi: "10.1145/2882903.2903741"
url: "https://doi.org/10.1145/2882903.2903741"
pdf_url: "[[The Snowflake Elastic Data Warehouse.pdf]]"
is_oa: false
date created: Sunday, July 20th 2025, 12:44:48 pm
date modified: Sunday, July 20th 2025, 1:24:33 pm
---

# Snowflake

Snowflake is a new cloud native platform for an enterprise-ready data warehouses in the cloud. Snowflake has full SQL support, is built on AWS, and has a multi-cluster, shared-data architecture, with a focus on elasticity.

Snowflakes features are:

- SaaS only: users don't provision compute or storage or install software. They upload data and query it immediately.
- Relational: supports SQL
- Semi-Structured: Snowflake has built-ins for traversing, flattening, and nesting JSON and Avro. There's also automatic schema discovery + columnar storage to save on cost.
- Elastic: Storage and compute can be scaled independently, without any impact on data availability
- Available: tolerates node, cluster, and data center failure. No downtime during upgrades.
- Durable: Data is cloned, and backed up.
- Cost-efficient: Snowflake is compute optimized, where all data is compressed.
- Secure: All traffic is encrypted end-to-end. There's also RBAC.

## Storage vs. Compute

Shared nothing architectures are commonplace in the industry, where each processor has its own local disks. This works fine but couples compute and storage, creating the following problems:

1. Heterogenous Workloads: workloads that are either high I/O and low compute or vice-versa are poor to run, since nodes will use either compute or storage well but not the other.
2. Membership Changes: If the set of nodes changes, because of node failure or cluster resizing, then nodes must send/receive data, impacting their performance during these changes.
3. Online Upgrade: It is hard to tolerate downtime for upgrades, and upgrading every node in a system is hard to do.

Snowflake instead separates storage and compute, which are handled by different services. Storage is on top of S3, and Compute is through the snowflake engine. Local data on compute instances is used for caching frequently used data.
## Architecture

There are three layers:

**Data storage**: (S3) The blob store that holds files on disk
**Virtual Warehouses**: (EC2) Handles query execution between elastic clusters of virtual machines
**Cloud Services**: Manages metadata, queries, transactions

### Data Storage

S3 was chosen over HDFS for usability, availability, and durability guarantees. However, files can only be overwritten in full, and it is impossible to append data. S3 does support GET requests for parts of a file. 

This influenced Snowflake's design to have horizontally partitioned tables as large immutable files, which have metadata that allow the files to be ranged over in search.

### Virtual Warehouses

This layer consists of EC2 clusters that make up a virtual warehouse. They are pure compute resources, which can be created, destroyed, or resized. Queries run on one virtual warehouse, where a query is split up among the worker nodes. If there's any partial failures, the entire query has to be rerun.

Each worker node has a cache of table data on local disk, and is shared between worker processes on the node. 

Nodes may be slower than others for many reasons. In this case, there's a work-stealing algorithm, where if a node falls behind on its work, another node can take some of its work and query from S3 for the table and work on that part.

### Execution Engine

- Tables are column major (for SIMD + CPU caching + compression)
- Vectorized (no materialization of intermediate results)
- Push-based (operators push downstream results, rather than pulling from upstream)

## Cloud Services

The Cloud Services layer contains long-lived and shared services. Some include Query optimization, and concurrency control. 

Of note: snowflake doesn't have indexes? it also supports MVCC SI, which is common (like in postgres)

### Pruning

Snowflake doesn't use indexes due to its different workloads: It has lots of random access, requires user maintenance, and is hard to share between nodes.

Instead, Snowflake uses min-max based pruning, materialized aggregates, zone maps, and data skipping. The system maintains statistics about a chunk of data, and then uses it to check if a file can be skipped in query. 

This works for all auto-detected columns of semi-structured data. As well, there's dynamic pruning during execution.

## Time Travel

Snowflake holds onto files for a configurable duration after they are deleted (90 days by default). As long as the older version is kept, time travel queries are also supported:

```sql
select * from my_table AT(TIMESTAMP => 'Mon, 01 May 2015 16:20:00 -7000'::timestamp); -- select at given timestamp
```

You can also access different versions of the same table in the same query

```sql
SELECT new.key, new.value, old.value from my_table as new JOIN my_table AT(OFFSET => -86400) old -- table from 1 day ago
ON new.key = old.key WHERE new.value <> old.value; -- join here
```