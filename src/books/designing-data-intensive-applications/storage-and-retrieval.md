---
title: storage-and-retrieval
---

and Retrieval"

# Storage and Retrieval

Prev:
[data-models-and-query-languages](data-models-and-query-languages.md)
Next:
[encoding-and-evolution](encoding-and-evolution.md)

## Data Structures That Power Your Database

Imagine this key-value database:

```sh
#!/bin/bash

db_set () {
  echo "$1,$2" >> database
}
db_get () {
  grep "^$1," database | sed -e "s/^$1,//" | tail -n 1
}
```

On `db_set`, it stores a key and its value. (O(1) time, since this
appends)

On `db_get`, it fetches the value that corresponds to the key, searching
backwards to the beginning of the dataset. (O(n) time).

We can do better by indexing:

## Hash Index

We can create an in-memory hash map where every key is mapped to a byte
offset in the data file. If you append a new key-value pair to the file,
update the hashmap to the location of the new value. This is what `Riak`
does.

We now have O(1) average reads.

### Implementation details:

1.  File Format

- Text formats are not particularly compact. Binary formats are
  better.

2.  Deleting records

- We can delete records by appending a tombstone to the hashmap. The
  tombstone tells the merging process to discard any previous values
  for the deleted key.

3.  Crash recovery

- Take a snapshot of the hashmap on disk intermittently, so when the
  database crashes, restarting it won't take so long.

4.  Partially written records

- Calculate a checksum for every log, allowing corrupted parts of the
  log to be detected and ignored.

5.  Concurrency control

- Writes should be strictly sequential, so there should be one writer
  thread that appends, with multiple reader threads.

### Hash Index in practice

### Pros

Appending is much faster than random writes, as random access writes can
be 100xs slower than a sequential write.

Concurrency and crash recovery are much easier, since incomplete writes
can be thrown away easily with checksums.

Merging avoids data fragmentation, which slows reads.

### Cons

The hash table should fit in memory. On disk hash indexes are much
slower.

Hash indexes are useless for range queries since they are unordered. For
example, a query like this does not use a hash index, and requires a
full table scan. A tree like index is sorted, and thus a query can use
it.

```sql
SELECT *
FROM table
WHERE income > 30000;
```

## SStables

SSTables are like our previous log structure, but they require that the
sequence of key-value pairs are sorted by key.

Indexes can be compacted using a mergesort like algorithm, reading the
input files side by side, looking at the first key in each file, copying
the lowest key to the output file, and repeating.

Since items are divided by time into segments, any items encountered
later that are in the set come later, so overwrite the ones that came
before with the ones that come later.

In order to find a particular key in the file, you dont need an index at
all -- you can use the byte offsets as a range query indicator.

Thus, the whole engine works like this:

- When a write comes in, add it to an in-memory balanced tree data
  structure (for example, a red-black tree). This in-memory tree is
  sometimes called a memtable.
- When the memtable gets bigger than some threshold---typically a few
  megabytes ---- write it out to disk as an SSTable file. This can be
  done efficiently because the tree already maintains the key-value
  pairs sorted by key. The new SSTable file becomes the most recent
  segment of the database. While the SSTable is being written out to
  disk, writes can continue to a new memtable instance.
- In order to serve a read request, first try to find the key in the
  memtable, then in the most recent on-disk segment, then in the
  next-older segment, etc.
- From time to time, run a merging and compaction process in the
  background to combine segment files and to discard overwritten or
  deleted values.

## LSM-Trees

SSTables can be combined to create an LSM-Tree, which is what LevelDB
and RocksDB do.

## BTrees

- Btrees are a balanced tree (like a Red-Black Tree) where all
  children are arrays. This allows Btrees to be compatible with range
  operators (`<`, `>`, `<=`, `>=`) and cache friendly.
- BTrees take up a significant amount of space alongside the table.
- They can fail when updating, so a WAL (Write Ahead Log) is sometimes
  used alongside it.

## Other Indexing Structures

It can be common to have a secondary index in a table, to index
something other than the primary key. This is common on read-heavy
tables (Think an accounts table, or a transactions table).

Some databases, like Postgres and MsSQL allow for partial indexes, where
an index only covers some of the data. This can be very useful in
certain cases.

### Multi-column Indexes

You can index columns at a time, like for geospatial data. (PostGIS with
a GIST (QuadTree or R-Tree) index)).

Here's an example of a 2D query:

```sql
SELECT *
FROM restaurants
WHERE latitude > 51.4946 AND latitude < 51.5079
  AND longitude > -0.1162 AND longitude < -0.1004;
```

### Full-text search and fuzzy indexes

Lucene uses edit distance along with an LSM-tree table for indexing.

### Keeping everything in memory

Disk offers two advantages over RAM. Disk is cheaper than RAM (~10x)
and durable, so it stores state after it is powered off (or crashes).

RAM is becoming far cheaper, which allows in-memory Key-value stores,
like Memcached and Redis to be doable.

In-memory key value databases still write to disk (normally in the form
of an append-only log) in order to allow for backups. They are fast as
they serve reads purely in memory, and come with some durability
guarantees because they write to disk. Because in-memory KV stores like
Redis don't have to worry about persisting data structures to disk,
some normally hard to represent data structures like queues and sets can
be found.

## Transaction Processing or Analytics?

- OLTP (Transaction Processing Systems)
  - You write and read small amounts of data to this system.
- OLAP (Analytics Systems)
  - Data Lakes for storing less frequently accessed data.
- ETL (Extract, Transform, Load) is used to get data into data
  warehouses for business analysts.

### Stars and Snowflakes: Schemas for Analytics

Data warehouses are used in a simple, formulaic style, known as a _star
schema_. At the center of the schema is a _fact table_, which represents
an event that occurred at a particular time.

A fact table might look like this:

date_key product_sk store_sk promotion_sk customer_sk quantity net_price discount_price

---

    140102        31      3          NULL           NULL          1          2.49        2.49
    140102        69      5          19             NULL          3          14.99       9.99
    140102        74      3          23             191           1          4.49        3.89

And it might have other tables like this product table it points to:

product_sk sku description brand category

---

       30       OK4012  Bananas       Freshmax     Fresh fruit
       31       KA9511  Fish food     Aquatech     Pet supplies
       32       AB1234  Croissant     Dealicious   Bakery

This is called a star schema, because all tables have a foreign key in
this single table.

## Column-Oriented Storage

Let's say we want to query a table for lots of rows but only a few
columns; say all purchases in 2013.

We'll need the date, the product_sk, the quantity, and price. How would
we do this efficiently?

In most RDBMS', data is stored by row. That means that filtering data
that is indexed is slow, as the engine must read the whole row into
memory before parsing and filtering it.

Column-oriented storage holds the values from each column together,
instead.

Instead of something like this, where data is accessed by row:

```py
[
# date_key, product_sk, store_sk
[140102, 69, 4],
[140102, 69, 5],
[140102, 74, 3]
]
```

Imagine a set of lists that contain all of their values:

```py
date_keys = [140102, 140102, 140102]
product_sks = [69, 69, 74]
store_sks = [4,5,3]
```

To reassemble a row, query the same index of all the rows.

### Run-Length Encoding

As well, this scheme lends itself well to Run-Length Encoding and opens
itself up to compression opportunities.

Let's take a look at our `product_sk` and make a bitmap of it instead.

```py
product_sks = [69, 69, 74]
product_sk_69 = [1, 1, 0]
product_sk_74 = [0, 0, 1]
```

We have two products, so we can generate two different bitmap arrays for
the values of `69` and `74`. Let's say we want to do a query like this:

```sql
SELECT date_key
FROM fact_table
WHERE product_sk = 69;
```

All we have to do is scan the `product_sk_69` bitmap to see that the
first two rows are set, and query those.

If we want to do something like this:

```sql
SELECT date_key
FROM fact_table
WHERE product_sk IN (69, 74);
```

We can bitwise OR the relevant bitmaps:

```py
product_sk_69_or_74 = [x | y for x, y in zip(product_sk_69, product_sk_74)]
# This is [1, 1, 1]
```

And use the relevant result of that.

In short, Column Storage is very efficient at using CPU-cycles.

### Sort Order in Column Storage

To sort data in a column, we can't sort one column at a time, since
that would break our scheme. A wise DB admin may choose to sort rows by
a frequently accessed column, like date, to make it so queries in a date
range are faster. They may also sort by second and third indicies, but
these have fewer speed gains.

## Writing to Column-Oriented Storage

Updating in place is impossible with a sorted column approach. However,
LSM trees work here, where all writes go to an in-memory store, and then
are added to a sorted structure and prepared for writing to disk.

## Aggregation: Data Cubes and Materialized Views

Views allow for faster reads in SQL databases. If we often run the same
set of queries, it's wasteful to run them without caching, as that
wastes compute. We can make a `view`, which is a table which is a
shortcut for writing a specific query. We can write a
`materialized view`, which is a persisted to disk copy of the data that
a query would produce.

On a write to a column that a materialized view depends on, the
materialized view needs to update itself, so they are more common on
read-heavy workloads.

A special case of this is a data cube or an OLAP cube. It is a grid of
aggregates grouped by dimension. This allows for a set of materialized
views to be grouped together on specific dimensions, allowing users to
query based on more dimensions that just a simple materialized view.
This can be a noticeable boost for some queries.

Prev:
[data-models-and-query-languages](data-models-and-query-languages.md)
Next:
[encoding-and-evolution](encoding-and-evolution.md)
