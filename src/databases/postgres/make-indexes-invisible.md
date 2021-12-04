---
title: make-indexes-invisible
---

Indexes Invisible

# Make Indexes Invisible

Postgres allows for transactional DDL, which allows you to compare a
query with and without an index very easily:

We see that this `SELECT` uses an index:

```sql
db= EXPLAIN
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';
                                         QUERY PLAN
--------------------
 Index Scan using sale_fact_sold_at_ix on sale_fact  (cost=0.42..182.80 rows=4319 width=41)
   Index Cond: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))
```

Let\'s drop the index inside of a transaction and see the query plan
aftewards:

```sql
db= BEGIN;
BEGIN

db= DROP INDEX sale_fact_sold_at_ix;
DROP INDEX

db= EXPLAIN
db- SELECT *
db- FROM sale_fact
db- WHERE sold_at BETWEEN '2020-07-01' AND '2020-07-31';
                                   QUERY PLAN
---------
 Seq Scan on sale_fact  (cost=0.00..2435.00 rows=4319 width=41)
   Filter: ((sold_at >= '2020-07-01'::date) AND (sold_at <= '2020-07-31'::date))

db= ROLLBACK;
ROLLBACK
```

**CAUTION**: This will lock out concurent selects, inserts, updates, and
deletes while the transcation is active:

Be careful using this in a testing environment, and be **extremely**
careful using this in a production database.
