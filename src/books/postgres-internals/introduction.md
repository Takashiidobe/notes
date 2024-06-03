---
title: "Introduction"
---

# Introduction

Next: [isolation](isolation.md)

Postgres manages data in databases, where a single instance can serve
many databases.

You first initialize a cluster.

Metadata for all cluster objects is stored in the system catalog.
Each database has its own set of tables and views that describe the
objects of the database.

Schemas store all objects of a database, with postgres defining a few
default ones:

- `pg_catalog` for system catalog tables,
- `information_schema` for the SQL standard metadata
- `pg_toast` for toast objects,
- `pg_temp` for temporary tables

Tablespaces define the physical data layout of objects, like a directory
in a file system.

Data can be distributed in a way that archived data goes on slow disks,
but actively updated data goes onto fast disks.

Tables, indexes, sequences, and materialized views are called relations
by postgres, which refers to rows.

Postgres stores relation in different forks, which are 1GB files that
store the physical data on disk.

The main fork stores rows or indexed rows.

The initialization fork stores data for unlogged tables, which are not
written to the WAL. Thus, they are fast but not durable.

The free space map keeps track of available space within pages. It is
used to find a page that can accommodate new data quickly.

The visibility map shows if a page needs to be vacuumed or frozen.

Postgres also stores large items that can be variable length in toast
tables.

Postgres runs a process based model, where the first process is called
"postmaster" and starts the rest with `fork`, like:

`startup`: restores the system after failure
`autovacuum`: removes stale data from tables and indexes
`wal writer`: writes WAL entries to disk
`checkpointer`: runs checkpoints
`writer`: flushes dirty pages to disk
`stats collector`: collects usage statistics for instance
`wal sender`: sends WAL entries to a replica
`wal receiver`: gets WAL entries on a replica

Postgres also maintains a process per connection. There's `pg_bouncer`
for connection pooling.

Next: [isolation](isolation.md)
