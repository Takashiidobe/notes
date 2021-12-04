---
title: btree-index
---

Index

# B-Tree Indexes

B-Tree indexes are the default index. They are a B-Tree (a balanced tree
with leaf nodes contained in arrays).

It can use the spaceship operator `<=>` (anything that fits comparisons)

As well, ranges, like `GROUP BY` and `ORDER BY` may use a B-Tree index.

B-Tree indexes can also be used on string matches, as long as you don\'t
wildcard match on the beginning:

```sql
select * from users where name like '%name'; -- Will not use an index
```

```sql
select * from users where name like 'name%'; -- may use an index.
```
