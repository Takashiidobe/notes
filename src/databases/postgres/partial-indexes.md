---
title: partial-indexes
---

Indexes

# Partial Indexes

We can create an index on only part of the table:

Taking an example of a `users` table with this schema and data:

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

We know that if we index the id of `users`, since we know that 90% of
the users aren\'t signed up, we can index only that part of the data:

```sql
db= CREATE INDEX users_unactivated_partial_ix ON users(id)
db- WHERE not activated;
CREATE INDEX
```

If we select using this index, the database uses this index:

```sql
db= EXPLAIN SELECT * FROM users WHERE not activated;
                                           QUERY PLAN
------------------------
 Index Scan using users_unactivated_partial_ix on users  (cost=0.29..3493.60 rows=102567 width=38)
```

And the index is about 10% the size of a full index:

```sql
db= \di+ users_unactivated_partial_ix
                                 List of relations
 Schema |           Name               | Type  | Owner | Table |  Size
--------+------------------------------+-------+-------+-------+---------
 public | users_unactivated_partial_ix | index | haki  | users | 2216 kB
```
