---
title: avoid-indexes-on-columns-with-low-selectivity
---

Indexes On Columns With Low Selectivity

# Avoid Indexes on Columns With Low Selectivity

Assume you have a `users` table:

```sql
db= CREATE TABLE users (
db-    id serial,
db-    username text,
db-    activated boolean
db-);
CREATE TABLE
```

Seed the table:

```sql
db= INSERT INTO users (username, activated)
db- SELECT
db-     md5(random()::text) AS username,
db-     random() < 0.9 AS activated
db- FROM
db-     generate_series(1, 1000000);
INSERT 0 1000000

db= SELECT activated, count(*) FROM users GROUP BY activated;
 activated | count
-----------+--------
 f         | 102567
 t         | 897433

db= VACUUM ANALYZE users;
VACUUM
```

And let\'s index it:

```sql
db= CREATE INDEX users_activated_ix ON users(activated);
CREATE INDEX
```

When querying _unactivated users_ the database uses the index:

```sql
db= EXPLAIN SELECT * FROM users WHERE NOT activated;
                                      QUERY PLAN
--------------
 Bitmap Heap Scan on users  (cost=1923.32..11282.99 rows=102567 width=38)
   Filter: (NOT activated)
   ->  Bitmap Index Scan on users_activated_ix  (cost=0.00..1897.68 rows=102567 width=0)
         Index Cond: (activated = false)
```

When you query for activated users, it doesn\'t use the index:

```sql
db= EXPLAIN SELECT * FROM users WHERE activated;
                          QUERY PLAN
---------------------------------------------------------------
 Seq Scan on users  (cost=0.00..18334.00 rows=897433 width=38)
   Filter: activated
```

This is because if Postgres deems that reading the index + the table is
worse than reading the whole table, it won\'t use the index.

If you have a table that is 10MB and an index that is 1MB, and 90% of
users are signed up, (10MB \* .9) = 9MB + 1MB index vs. 10MB table read
is about the same. So Postgres may choose to read the whole table
instead.
