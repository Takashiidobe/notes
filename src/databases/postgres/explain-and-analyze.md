---
title: explain-and-analyze
---

And Analyze

# Explain & Analyze

## Explain

Explain generates a query plan by **estimating** the cost.

This is a sequential scan on a table `users`.

```sql
EXPLAIN SELECT * FROM users;

                       QUERY PLAN
---------------------------------------------------------
 Seq Scan on users  (cost=0.00..155.00 rows=10000 width=4)
(1 row)
```

We can format this in JSON if we so desire:

```sql
EXPLAIN (FORMAT JSON) SELECT * FROM users;
           QUERY PLAN
----------------------------------
 [                               +
   {                             +
     "Plan": {                   +
       "Node Type": "Seq Scan",  +
       "Relation Name": "users", +
       "Alias": "users",         +
       "Startup Cost": 0.00,     +
       "Total Cost": 155.00,     +
       "Plan Rows": 10000,       +
       "Plan Width": 4           +
     }                           +
   }                             +
 ]
```

If there is an index, and the query uses it (normally with a `WHERE`
statement)

```sql
EXPLAIN SELECT * FROM foo WHERE i = 4;

                         QUERY PLAN
--------------------------------------------------------------
 Index Scan using fi on foo  (cost=0.00..5.98 rows=1 width=4)
   Index Cond: (i = 4)
(2 rows)
```

## Explain Analyze

Explain analyze actually runs the query in question: if you want to run
a query that has side effects (i.e. queries that aren\'t `SELECT`s), you
will want to run `EXPLAIN ANALYZE` in a transaction.

Always do something like this:

```sql
BEGIN;
EXPLAIN ANALYZE ...;
ROLLBACK;
```
