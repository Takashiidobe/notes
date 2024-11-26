---
title: mysql-8
date created: Friday, November 22nd 2024, 9:49:28 am
date modified: Friday, November 22nd 2024, 10:17:44 am
---

- Atomic DDL statements are now supported.
You can now do CREATE, ALTER, DROP, TRUNCATE TABLE.

[innodb_deadlock_detect](https://dev.mysql.com/doc/refman/8.0/en/innodb-parameters.html#sysvar_innodb_deadlock_detect) can be used to disable deadlock detection.

select for share and select for update now has NOWAIT and SKIP LOCKED which causes the statement to return immediately. SKIP LOCKED removes locked rows from the result set. NOWAIT allows you to immediately throw a lock acquisition failure which can be useful in case of looping. Skip locked never waits as well.

ALGORITHM=INSTANT is supported for ALTER TABLE operations. This is done by default.
- adding a column
- adding/dropping a virtual column
- adding/dropping a column default value
- modifying the definition of an enum/set column
- changing index type
- renaming a table

