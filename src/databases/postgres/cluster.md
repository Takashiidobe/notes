---
title: cluster
---

# Cluster

Cluster allows you to sort a table by a specific index:

Imagine this table:

```sql
db= TRUNCATE sale_fact;
TRUNCATE TABLE

-- Insert rows without sorting
db= INSERT INTO sale_fact (username, sold_at)
db- SELECT
db-     md5(random()::text) AS username,
db-     '2020-01-01'::date + (interval '1 day') * round(random() * 365 * 2) AS sold_at
db- FROM
db-     generate_series(1, 100000)
INSERT 0 100000

db= ANALYZE sale_fact;
ANALYZE

db= SELECT tablename, attname, correlation
db- FROM pg_stats
db- WHERE tablename = 'sale_fact';

  tablename | attname  |  correlation
-----------+-----------+----------------
 sale_fact | sold_at   | -5.9702674e-05
 sale_fact | id        |              1
 sale_fact | username  |    0.010033822
```

We have 0 correlation on `sold_at`, so if we query using a `WHERE` on
`sold_at`, we\'ll get a `Bitmap Heap Scan`, which will be much slower
than an `Index Scan`.

Let\'s cluster on our `sold_at` index.

```sql
db= CLUSTER sale_fact USING sale_fact_sold_at_ix;
CLUSTER

db= ANALYZE sale_fact;
ANALYZE

db= SELECT tablename, attname, correlation
db- FROM pg_stats
db- WHERE tablename = 'sale_fact';

 tablename | attname  | correlation
-----------+----------+--------------
 sale_fact | sold_at  |            1
 sale_fact | id       | -0.002239401
 sale_fact | username |  0.013389298
```

Clustering affects the correlatio of other columns, like `id`, which
went from being a correlation of `1` to `0`. Try to avoid this by
inserting data sorted, by inserting the data with an `ORDER BY`.

Compare that table above with a correlation table using an `ORDER BY` on
an insert:

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

Queries that use the `id` index and `sold_at` index will be much faster,
whereas with a cluster, only queries on `sold_at` will be fast.
