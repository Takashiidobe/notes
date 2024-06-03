---
title: "Pages and Tuples"
---

# Pages and Tuples

Prev: [isolation](isolation.md)
Next: [snapshots](snapshots.md)

## Page Structure

Each page has a layout that consists of the following parts:

- page header
- an array of item pointers
- free space
- items (row versions)
- special space

Page Header

The page header is located first, and has a fixed size. It stores
metadata about the page, like its checksum and the sum of the other
sizes of the page.

Special Space

The special space is the last part of the page, and is used by indexes
to store auxiliary information.

Tuples

Rows contain the actual data stored in the database. They are located
before the special space. Tables have to select row versions than rows,
because of MVCC, and indexes do not use MVCC. Instead, they reference
the available row versions.

Item Pointers

The array of pointers points to each item, using indirect addressing.
Each pointer takes 4 bytes, and indicates the following:

- Tuple offset from the start of the page
- Tuple length
- Several bits defining the tuple status

Free space

- All unused space

## Row version layout

Each row version contains a header followed by data:

The header has;

- `xmin`, `xmax`, the transaction ids that differentiate this row from
other versions of the same row
- `infomask` information bits that define version properties
- `ctid` a pointer to the next updated version of the same row
- `null bitmap` an array of bits marking the columns that contain null
  values

## Operations on Tuples

- on creation, a tuple's `xmin` is set to the `txid` of the insert
  command.
- on deletion, the `xmax` is set to the `txid` of the deletion command.
- on update, the old tuple is deleted, and a new tuple is created, so it
  does both create and delete operations.

Transactions are saved in the commit log file. Postgres uses this to
figure out which transactions have been committed when reading.

## Indexes

Indexes do not use row versioning, and store all versions of the
corresponding table row. Transactions have to read the table to see
which versions are readable.

## Toast

A toast table is virtually a regular table, and has its own versioning.

## Virtual Transactions

If a transaction is read-only, it does not affect row visibility in any
way. So transactions are given a virtual txid, which doesn't require any
synchronization.

## Subtransactions

SQL supports savepoints, which enable canceling some of the operations
within a transaction without aborting the transaction as a whole.

## Errors

If an error occurs during execution of a statement, the transaction is
rolled back by default. This is because we could get access to changes
made before the error, breaking atomicity of the statement.

Prev: [isolation](isolation.md)
Next: [snapshots](snapshots.md)
