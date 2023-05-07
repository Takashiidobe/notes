---
title: "Database Storage II"
---

# Database Storage II

Prev: [database-storage-i](database-storage-i.md)
Next: [buffer-pools](buffer-pools.md)

## Data Representation

Tuples are just byte arrays on disk. The DBMS needs to interpret those bytes accordingly.

**Integers**

BIGINT = i64
INTEGER = i32
SMALLINT = i16
TINYINT = i8

**Variable Precision Numbers**

- Inexact, variable-precision numeric types that use the IEEE-754 floating point numbers.

FLOAT = f64
REAL = f32

**Fixed Point Precision Numbers**

- Numeric data types with arbitrary precision and scale.

NUMERIC, DECIMAL

**Variable Length Data**

- An array of bytes of arbitrary length.
- Generally a header with length of bytes + the bytes themselves.
- Some systems will let you store large values in an external file, and then the tuple will contain a pointer to that file. This is called a `BLOB` normally.

VARCHAR, VARBINARY, TEXT, BLOB

**Dates and Times**

- Datetime Representations as the number of micro/milliseconds since the unix epoch.

TIME, DATE, TIMESTAMP

## Workloads

**OLTP**: On-line Transaction Processing
- Fast, short running operations
- Queries operate on a single entity at a time
- More writes that reads
- repetitive operations

**OLAP**: On-line Analytical Processing
- Long running, complex queries
- Reads large parts of the database
- More reads than writes
- Exploratory queries

## Storage Models

**N-Ary Storage Model (NSM)**

Stores all the attributes for a single tuple contiguously, so NSM is known as a "row store". Useful for OLTP workloads.

Advantages:
- Fast insert, updates, and deletes
- Fast if data is accessed by row

Disadvantages:
- Slow + wasteful if scanning by singular or multiple attributes column wise.

There are two ways to organize an NSM database:

- **Heap-Organized** Tuples are stored in a heap, which is orderless.
- **Index-Organized** Tuples are stored in the primary key index.

**Decomposition Storage Model (DSM)**

Stores all attributes for all tuples contiguously in a block of data. A "column store". Ideal for OLAP workloads.

Advantages:
- Reduces the amount of wasted work, since DBMS only reads data required.
- Enables better compression of values, since they are more likely to be similar

Disadvantages:
- Slow for point queries, inserts, updates, and deletes due to tuple stitching/splitting.

To put tuples back together, databases can set fixed-size offsets, or embed the tuple id inside the attribute of each column, to allow for faster jumping to specific attributes.

Prev: [database-storage-i](database-storage-i.md)
Next: [buffer-pools](buffer-pools.md)
