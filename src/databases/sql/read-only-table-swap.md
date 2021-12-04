---
title: read-only-table-swap
---

Only Table Swap

# Read Only Table Swap

Imagine you have a scenario where you have a large table which stores
referential information. Imagine that this table stores millions of rows
of read-only data, and needs to be updated every so often (maybe every
day).

First approach: Every day, run a job that truncates the existing table
and then insert the new rows.

Pros:

- Simple

Cons:

- Truncate commits a transaction (on MySQL 5.x and certain vendors),
  so if the insertion fails, you are left with an empty table.

Second approach: Every day, run a job that creates a different table,
inserts the new rows into that table, and then swaps the table.

Pros:

- All of the actions an be rolled into one transaction.
- If any part of it fails, you can send an alert and fix it
  immediately.

Cons:

- Longer query which lowers database performance while it executes.

To do the swap, we will do the following.

```sql
START TRANSACTION;
CREATE TABLE ${new-table} LIKE ${table-to-replace};
INSERT INTO ${table-to-replace} (${columns}) VALUES (${rows});
RENAME TABLE ${table-to-replace} TO ${table-to-drop}, ${new-table} TO ${table-to-replace};
DROP TABLE ${table-to-replace};
COMMIT;
```

If any of the above fails, nothing will happen; then we can figure out
why the operation failed.
