---
title: unlogged-tables
---

Tables

# Unlogged Tables

Unlogged tables don\'t write to the WAL (Write Ahead Log). This can make
them faster if you don\'t care about persisting their changes to the DB.

For example, intermediate tables don\'t need to be restored, so you can
use `UNLOGGED`.

```sql
CREATE UNLOGGED TABLE staging_table (...);
```
