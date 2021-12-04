---
title: type-casting
---

Casting

# Type casting

Postgres offers two different syntaxes for Type casts:

```sql
CAST (expression AS type)
```

or

```sql
expression::type
```

For example:

```sql
CAST ('{1,2,3}' as int[]) -- casts a string to an int[]
'{1,2,3}'::int[] -- casts a string to an int[]
```
