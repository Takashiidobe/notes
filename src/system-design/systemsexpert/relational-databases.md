---
title: Relational Databases
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:40:27 pm
---

# Relational Databases

- Imposes Tabular style organization:
- Everything is a table.
- Rows are often referred to as Records.
- The data stored in them are well defined.
- NoSQL are hard to query, whereas RDBMS use powerful SQL.
- SQL follows ACID transactions:

  - Atomic:
    - If a transaction contains more than one transaction, they
      are grouped as one unit: If one operation fails, the whole
      transaction fails.
  - Consistency:
    - There is no stale state in the database. Everything is kept
      up to date.
  - Isolation:
    - Each Operation is done in the database as if sequential.
  - Durability:
    - The effects of an Operation is stored on disk forever.

- Indexing:

  - Indexes allow for fast reads of a table:
    - if you have to find one record on an unsorted table, that is
      an O(n) operation.
    - If we index it (restructure the table as a tree), this can
      take O(log n) time.
    - They do cost extra space, and increase memory usage.

- Remember to always write queries as transactions:

```sql
BEGIN TRANSACTION;

-- ROLLBACK if condition is not met
- ROLLBACK;

COMMIT;
```

Effectively, SQL is run sequentially.

Prev: \[hashing](hashing.md) Next:
\[key-value-stores](key-value-stores.md)
