---
title: brin-index
---

Index

# BRIN Index

BRIN stands for Block Range Index:

This stores a range of values within a number of adjacent pages in the
table.

![Brin Index](./brin-index.svg)

Take an example of 9 numbers, divided into three pages
(`pages_per_range` is used to change this setting):

```sql
1, 2, 3, 4, 5, 6, 7, 8, 9
```

```sql
[1,2,3], [4,5,6], [7,8,9]
```

A BRIN index keeps the minimum and maximum values of each block:

That way, when we use the index to find the value 5:

We know this:

- \[1--3\] - Definitely not here
- \[4--6\] - Might be here
- \[7--9\] - Definitely not here

If we don\'t have sorted data, or loosely correlated data:

```sql
[2,9,5], [1,4,7], [3,8,6]
```

The ranges look like this:

```sql
[2–9], [1–7], [3–8]
```

Looking at the index, we find this:

- \[2--9\] - Might be here
- \[1--7\] - Might be here
- \[3--8\] - Might be here

The index is useless, so the query planner will most likely not use it:

## Creating a BRIN index:

We create a BRIN index like so:

```sql
db= CREATE INDEX sale_fact_sold_at_bix ON sale_fact
db- USING BRIN(sold_at) WITH (pages_per_range = 128);
CREATE INDEX
```

```sql
db= EXPLAIN (ANALYZE)
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';
                                    QUERY PLAN
--------------------
 Bitmap Heap Scan on sale_fact  (cost=13.11..1135.61 rows=4319 width=41)
   Recheck Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
   Rows Removed by Index Recheck: 23130
   Heap Blocks: lossy=256
   ->  Bitmap Index Scan on sale_fact_sold_at_bix  (cost=0.00..12.03 rows=12500 width=0)
         Index Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
 Execution Time: 8.877 ms
```

We removed \~23000 rows, which costs a lot of I/O.

If we drop the `pages_per_range` to 64:

```sql
db= CREATE INDEX sale_fact_sold_at_bix64 ON sale_fact
db- USING BRIN(sold_at) WITH (pages_per_range = 64);
CREATE INDEX
```

We get only \~9400 rows checked, and a query time of \~5.5ms, compared
to the \~8.8ms from before, a \~45% speedup.

```sql
db= EXPLAIN (ANALYZE)
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';
                                        QUERY PLAN
---------------------
 Bitmap Heap Scan on sale_fact  (cost=13.10..1048.10 rows=4319 width=41)
   Recheck Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
   Rows Removed by Index Recheck: 9434
   Heap Blocks: lossy=128
   ->  Bitmap Index Scan on sale_fact_sold_at_bix64  (cost=0.00..12.02 rows=6667 width=0)
         Index Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
 Execution Time: 5.491 ms
```

## BRIN Index Size

As you can see, the BRIN Index (by default) is \~50 times smaller than
the B-Tree index, and can have some performance gains.

```sql
 Schema |         Name          | Type  | Owner |   Table   | Size
--------+-----------------------+-------+-------+-----------+-------
 public | sale_fact_sold_at_bix | index | haki  | sale_fact | 48 kB
 public | sale_fact_sold_at_ix  | index | haki  | sale_fact | 2224 kB
```
