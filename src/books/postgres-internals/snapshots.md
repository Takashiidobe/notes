---
title: "Snapshots"
---

# Snapshots

Prev: [pages-and-tuples](pages-and-tuples.md)
Next: [page-pruning-and-hot-updates](page-pruning-and-hot-updates.md)

## What is a Snapshot?

A data table contains several versions of the same row, and transactions
should only show one of them at most.

Visible versions of the different rows are a snapshot.

Each transaction uses its own snapshot:

**Read committed** takes a snapshot at the beginning of each statement.
**Repeatable Read** and **Serializable** takes a snapshot at the
beginning of the first statement of a transaction.

## Row Version Visibility

Tuple visibility is defined by the *xmin* and *xmax* fields of the tuple
header.

## Snapshot Structure

The ProcArray structure in the server contains the list of all active
transactions at a point in time.

## Transaction Horizon

The horizon of the transaction is the smallest xmin of the active snapshot for
the transaction. This is important because any other tuples with a lower
xmin aren't required for the transaction.

The horizon for the database is the smallest xmin for all active transactions in
the database. Any tuples below this can be removed, and are taken care
of by the vacuuming process.

Prev: [pages-and-tuples](pages-and-tuples.md)
Next: [page-pruning-and-hot-updates](page-pruning-and-hot-updates.md)
