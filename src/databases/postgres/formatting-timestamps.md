---
title: formatting-timestamps
---

Timestamps

# Formatting Timestamps

- Format a timestamp with:

```sql
SELECT to_char(now() - '2020-05-28 5:30'::timestamp, 'HH:MI');
```

[`DateTime Formatting in Postgres`](https://www.postgresql.org/docs/current/functions-formatting.md)

Convert a timestamp to minutes:

```sql
SELECT extract(epoch from (now() - '2020-05-28 5:30'::timestamp)) / 60;
```
