---
title: always-load-sorted-data
---

Load Sorted Data

# Always Load Sorted Data

Assume we have a large sales fact table:

```sql
db= CREATE TABLE sale_fact (id serial, username text, sold_at date);
CREATE TABLE
```

Let\'s say we load data to the table every night:

```sql
db= INSERT INTO sale_fact (username, sold_at)
db- SELECT
db-     md5(random()::text) AS username,
db-     '2020-01-01'::date + (interval '1 day') * round(random() * 365 * 2) AS sold_at
db- FROM
db-     generate_series(1, 100000);
INSERT 0 100000

db= VACUUM ANALYZE sale_fact;
VACUUM
```

We index for fast querying:

```sql
db= CREATE INDEX sale_fact_sold_at_ix ON sale_fact(sold_at);
CREATE INDEX
```

And then we use the index in a query:

```sql
db= EXPLAIN (ANALYZE)
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';

                            QUERY PLAN
-----------------------
 Bitmap Heap Scan on sale_fact  (cost=108.30..1107.69 rows=4293 width=41)
   Recheck Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
   Heap Blocks: exact=927
   ->  Bitmap Index Scan on sale_fact_sold_at_ix  (cost=0.00..107.22 rows=4293 width=0)
         Index Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
 Planning Time: 0.191 ms
 Execution Time: 5.906 ms
```

This does a `Bitmap Heap Scan`, which has two parts:

- a `Bitmap Index Scan`, which goes through the entire index and maps
  all the table pages that contain relevant rows:
- a `Bitmap Heap Scan`, which reads the pages that contain relevant
  rows, and checks to make sure that rows satisfy the condition.

This takes \~6ms to do.

We can make this better by sorting the data after loading it:

```sql
db= TRUNCATE sale_fact;
TRUNCATE TABLE

db= INSERT INTO sale_fact (username, sold_at)
db- SELECT
db-     md5(random()::text) AS username,
db-     '2020-01-01'::date + (interval '1 day') * round(random() * 365 * 2) AS sold_at
db- FROM
db-     generate_series(1, 100000)
db- ORDER BY sold_at;
INSERT 0 100000

db= VACUUM ANALYZE sale_fact;
VACUUM
```

We include an `ORDER BY` on the column we query, so the table inserts
and then sorts.

When querying now we see this:

```sql
db= EXPLAIN (ANALYZE)
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';

                           QUERY PLAN
---------------------
 Index Scan using sale_fact_sold_at_ix on sale_fact (cost=0.29..184.73 rows=4272 width=41)
   Index Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
 Planning Time: 0.145 ms
 Execution Time: 2.294 ms
```

This query now only uses the index, and trusts that the data is in
order. Querying data in order is almost always faster (think of a range
query over a sorted vector over an unsorted vector),

This works because of `Correlation`.

> Statistical correlation between physical row ordering and logical
> ordering of the column values. This ranges from -1 to +1. When the
> value is near -1 or +1, an index scan on the column will be estimated
> to be cheaper than when it is near zero, due to reduction of random
> access to the disk.

Correlation of 1:

![Correlation = 1](./correlation-1.svg)

Correlation of 0:

![Correlation ~ 0](./correlation-0.svg)

We can query the correlation of `sold_at` by looking at the `pg_stats`
for the table:

Before inserting it sorted:

```sql
db= SELECT tablename, attname, correlation
db- FROM pg_stats
db= WHERE tablename = 'sale_fact';

 tablename | attname  | correlation
-----------+----------+--------------
 sale      | id       |            1
 sale      | username | -0.005344716
 sale      | sold_at  | -0.011389783
```

Afterwards:

```sql
db= SELECT tablename, attname, correlation
db- FROM pg_stats
db= WHERE tablename = 'sale_fact';
 tablename | attname  |  correlation
-----------+----------+----------------
 sale_fact | id       |              1
 sale_fact | username | -0.00041992788
 sale_fact | sold_at  |              1
```

We can see that when the correlation is close to 1 or -1, that the table
will be more likely to use an `Index Scan` instead of a
`Bitmap Heap Scan`, and this is likely to be faster.
