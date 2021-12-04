---
title: coalesce
---

# Coalesce

Coalesce returns the first argument that returns non-null, or null.

```sql
SELECT COALESCE (1,2);
1
```

Imagine we have this table (note the `NULL`):

```sql
INSERT INTO items (product, price, discount)
VALUES
    ('A', 1000 ,10),
    ('B', 1500 ,20),
    ('C', 800 ,5),
    ('D', 500, NULL);
```

If we try to subtract the price without checking for `NULL`, we\'ll get
null for the last row:

We can use coalesce to catch for `NULL`s.

```sql
SELECT
    product,
    (price - COALESCE(discount,0)) AS net_price
FROM
    items;
```
