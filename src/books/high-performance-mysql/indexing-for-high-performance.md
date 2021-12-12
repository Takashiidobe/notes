---
title: "Indexing for High Performance"
---

# Indexing for High Performance

Prev: [schema-design-and-management](schema-design-and-management.md)
Next: [query-performance-optimization](query-performance-optimization.md)

## Indexing Basics

An Index contains values from one or more columns in a table.

## Types of Indexes

### B-tree

B-tree is the table index in mySQL. It speeds up CRUD operations by
making them O(log n) time.

Indexes in MySQL are called key:

So this sql indexes all the values in the People Table.

```sql
CREATE TABLE People (
 last_name varchar(50) not null,
 first_name varchar(50) not null,
 dob date not null,
 key(last_name, first_name, dob)
);
```

As well, InnoDB has a feature called `adaptive hash indexes`, which adds
a hash-index on commonly accessed B-Tree tuples.

### Types of queries that can use a B-tree index

- Full Value
- Leftmost prefix
- Column Prefix
- Range of Values
- One part and a range on others

The Order of the indexing is important, because MySQL accesses indexes
from left to right. In the above sql, we index by last name, so
searching for `dob` is less useful than filtering on `last_name`.

### Full-text Indexes

Full Text indexes are used like search engines, except they use `MATCH AGAINST` instead of `WHERE` for parameter matching.`

## Benefits of Indexes

Indexes hold data in sorted order, which helps the server reduce the
amount of data to go through, and helps the server avoid sorting and
temporary tables.

### Indexing Strategies for High Performance

#### Prefix Indexes and Index Selectivity

Space can be saved by only indexing the beginning (the left hand side)
of a key instead of the whole key.

More unique indexes are higher in index selectivity, which helps in
query performance as well.

BLOBs and TEXT columns force this on you by defining prefix indexes.

As well, you should be using `EXPLAIN` to let the optimizer explain to
you why it prefers a specific query plan.

To find a good length for selectivity, you can calculate the selectivity
of each column:

```sql
mysql> SELECT COUNT(DISTINCT city)/COUNT(*) FROM sakila.city_demo;
+-------------------------------+
| COUNT(DISTINCT city)/COUNT(*) |
+-------------------------------+
|                        0.0312 |
+-------------------------------+
```

Or for many columns:
It seems like 5, 6, 7 are good index lengths for this column.

```sql
mysql> SELECT COUNT(DISTINCT LEFT(city, 3))/COUNT(*) AS sel3,
    -> COUNT(DISTINCT LEFT(city, 4))/COUNT(*) AS sel4,
    -> COUNT(DISTINCT LEFT(city, 5))/COUNT(*) AS sel5,
    -> COUNT(DISTINCT LEFT(city, 6))/COUNT(*) AS sel6,
    -> COUNT(DISTINCT LEFT(city, 7))/COUNT(*) AS sel7
    -> FROM sakila.city_demo;
+--------+--------+--------+--------+--------+
| sel3   | sel4   | sel5   | sel6   | sel7   |
+--------+--------+--------+--------+--------+
| 0.0239 | 0.0293 | 0.0305 | 0.0309 | 0.0310 |
+--------+--------+--------+--------+--------+
```

Once we find that `7` is a good value, we can add it to our database:

```sql
ALTER TABLE sakila.city_demo ADD KEY (city(7));
```

### Multicolumn Indexes

Individual indexes on lots of columns won't help MySQL much. That being
said, it can do a strategy called `index merge` where it uses multiple
indexes on a single table and merges the results for a query. This
speeds up performance but might indicate poor indexes.

If there's an index merge in `EXPLAIN`, you can glean the following:

1. If the server intersects indexes, (usually for `AND` conditions) you
   should have a single index with all relevant columns instead of
   multiple indexes.
2. When the server unions indexes (usually for `OR` conditions) the
   indexes should be more selective.

### Choosing a Good Column Order

Since B-Trees sort from the left, a good column is extremely important.

We could try to index based on selectivity:

So in this case, `customer_id` should come first.

```sql
mysql> SELECT COUNT(DISTINCT staff_id)/COUNT(*) AS staff_id_selectivity,
    -> COUNT(DISTINCT customer_id)/COUNT(*) AS customer_id_selectivity,
    -> COUNT(*)
    -> FROM payment\G
*************************** 1. row ***************************
 staff_id_selectivity: 0.0001
 customer_id_selectivity: 0.0373
 COUNT(*): 16049
```

However, indexes don't always work:

Take this query:

```sql
SELECT COUNT(DISTINCT threadId) AS COUNT_VALUE
FROM Message
WHERE (groupId = 10137) AND (userId = 1288826) AND (anonymous = 0)
ORDER BY priority DESC, modifiedDate DESC
```

Explain shows that this uses an index on (groupId, userId).

```sql
id: 1
 select_type: SIMPLE
 table: Message
 type: ref
 key: ix_groupId_userId
 key_len: 18
 ref: const,const
 rows: 1251162
 Extra: Using where
```

But in this case, no indexes will help, due to the fact that this query
triplet has to scan through almost every row in the table.

```sql
mysql> SELECT COUNT(*), SUM(groupId = 10137),
    -> SUM(userId = 1288826), SUM(anonymous = 0)
    -> FROM Message\G
*************************** 1. row ***************************
 count(*): 4142217
 sum(groupId = 10137): 4092654
 sum(userId = 1288826): 1288496
 sum(anonymous = 0): 4141934
```

### Clustered Indexes

Clustered indexes store all rows in the index's leaf pages, with
adjacent key values stored close to one another.

There is a limit of one clustered index per table. Covering indexes
allow you to emulate multiple clustered indexes, however.

Clustering data has advantages:

1. Related data is close together.
2. Data access is fast: the index holds the index and the data.

And disadvantages:

1. Only gives I/O bound advantages.
2. Insert speeds depend heavily on insertion order. It might be a good
   idea to reorganize the table with `OPTIMIZE TABLE` after loading a
   lot of data if the data wasn't loaded in primary key order.
3. Updating clustered indexes is more expensive than a regular index
4. If a new row is inserted, a page split might occur, which causes
   inserts to sometimes be slower and use more space on disk.
5. Clustered tables are slower for full table scans, especially if not
   `OPTIMIZE TABLE`d.
6. Secondary index accesses require two index lookups instead of one.

### InnoDB's data layout

```sql
CREATE TABLE layout_test (
 col1 int NOT NULL,
 col2 int NOT NULL,
 PRIMARY KEY(col1),
 KEY(col2)
);
```

For this table, each row contains `col1`, `col2`, the transaction id,
the primary key (col2) and the rollback pointer InnoDB uses for
transactional and MVCC purposes.

### inserting rows in Primary key order with InnoDB

It may be a good idea to define a `surrogate key`, which is a primary
key whose value is not derived from the data.

It's best to avoid random (nonsequential and distributed) clustered
keys, especially for I/O-bound workloads. UUIDs are a big offender of
this, as they make clustering harder, and indexes perform worse off.

Take this example table which has an unsigned int as primary key:

```sql
CREATE TABLE userinfo (
 id int unsigned NOT NULL AUTO_INCREMENT,
 name varchar(64) NOT NULL DEFAULT '',
 email varchar(64) NOT NULL DEFAULT '',
 password varchar(64) NOT NULL DEFAULT '',
 dob date DEFAULT NULL,
 address varchar(255) NOT NULL DEFAULT '',
 city varchar(64) NOT NULL DEFAULT '',
 state_id tinyint unsigned NOT NULL DEFAULT '0',
 zip varchar(8) NOT NULL DEFAULT '',
 country_id smallint unsigned NOT NULL DEFAULT '0',
 gender ('M','F')NOT NULL DEFAULT 'M',
 account_type varchar(32) NOT NULL DEFAULT '',
 verified tinyint NOT NULL DEFAULT '0',
 allow_mail tinyint unsigned NOT NULL DEFAULT '0',
 parrent_account int unsigned NOT NULL DEFAULT '0',
 closest_airport varchar(3) NOT NULL DEFAULT '',
 PRIMARY KEY (id),
 UNIQUE KEY email (email),
 KEY country_id (country_id),
 KEY state_id (state_id),
 KEY state_id_2 (state_id,city,address)
) ENGINE=InnoDB
```

Vs. the same table but with a uuid as the primary key.

```sql
CREATE TABLE userinfo_uuid (
 uuid varchar(36) NOT NULL,
 ...
)
```

First, both tables were inserted with a million rows, so the index could
fit into memory:

Then, 3 million rows of random data, which wouldn't fit in memory.

Note how the time to insert the rows for UUID is substantially slower
(3x+ when writing to disk) and the index is 70% larger.

| Table         | Rows      | Time (sec) | Index size (MB) |
| ------------- | --------- | ---------- | --------------- |
| userinfo      | 1,000,000 | 137        | 342             |
| userinfo_uuid | 1,000,000 | 180        | 544             |
| userinfo      | 3,000,000 | 1233       | 1036            |
| userinfo_uuid | 3,000,000 | 4525       | 1707            |

This happens because InnoDB can store the data immediately after the
previous insert in case of an `AUTO_INCREMENT` primary key, but for a
UUID key, where the distribution is random, may have to flush pages more
often and seek to random places in its in memory buffer to place
records.

This can be improved somewhat with `OPTIMIZE TABLE`, to allow InnoDB to
reorder records.

### When primary key order is worse

Primary Key order can be worse for high-concurrency workloads, because
`AUTO_INCREMENT` requires taking a lock. It could be possible that
removing the auto incrementing public key would be better for
performance.

## Covering Indexes

When a query is covered by an index, you'll see `Using index` in the
extra column of explain:

```sql
mysql> EXPLAIN SELECT store_id, film_id FROM sakila.inventory\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: inventory
 partitions: NULL
 type: index
 possible_keys: NULL
 key: idx_store_id_film_id
 key_len: 3
 ref: NULL
 rows: 4581
 filtered: 100.00
 Extra: Using index
```

InnoDB indexes by primary key, so even though the index might not
normally cover the data, it can be used: In this case, `actor_id`, the
primary key, isn't indexed, but can be used here:

```sql
mysql> EXPLAIN SELECT actor_id, last_name
    -> FROM sakila.actor WHERE last_name = 'HOPPER'\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: actor
 partitions: NULL
 type: ref
 possible_keys: idx_actor_last_name
 key: idx_actor_last_name
 key_len: 182
 ref: const
 rows: 2
 filtered: 100.00
 Extra: Using index
```

### Using Index Scans for Sorts

MySQL can use indexes for sorting and finding rows. Ordering the results
by index works only when the index's order is exactly the same as the
`ORDER BY` clause, and all columns are sorted in the same direction
(`ASC` or `DESC`). If not, then MySQL will use a sort.

This can be checked in the `type` of `EXPLAIN`:

```sql
mysql> EXPLAIN SELECT rental_id, staff_id FROM sakila.rental
    -> WHERE rental_date = '2005-05-25'
    -> ORDER BY inventory_id, customer_id\G
*************************** 1. row ***************************
 type: ref
 possible_keys: rental_date
 key: rental_date
 rows: 1
 Extra: Using where
```

Indexes can be forced in MySQL, if the optimizer doesn't do what you
want.

## Redundant and Duplicate Indexes

Duplicate indexes are indexes of the same type created on the same
columns:

```sql
CREATE TABLE test (
 ID INT NOT NULL PRIMARY KEY,
 A INT NOT NULL,
 B INT NOT NULL,
 UNIQUE(ID),
 INDEX(ID)
) ENGINE=InnoDB;
```

This creates 3 Unique indexes on the same key (ID). InnoDB only warns
you of duplicate indexes. Remove them if possible.

Redundant Indexes are like the following:

If there's an index on `(A, B)`, then another index on `(A)` is
redundant, because all lookups will use the index `(A, B)` anyway.

However, an index on `(B, A)` or `(B)` would not be redundant, because B
is not a left-most prefix of the index `(A, B)`.

That being said, sometimes redundant indexes are desirable for
performance reasons:

```sql
REATE TABLE userinfo (
 id int unsigned NOT NULL AUTO_INCREMENT,
 name varchar(64) NOT NULL DEFAULT '',
 email varchar(64) NOT NULL DEFAULT '',
 password varchar(64) NOT NULL DEFAULT '',
 dob date DEFAULT NULL,
 address varchar(255) NOT NULL DEFAULT '',
 city varchar(64) NOT NULL DEFAULT '',
 state_id tinyint unsigned NOT NULL DEFAULT '0',
 zip varchar(8) NOT NULL DEFAULT '',
 country_id smallint unsigned NOT NULL DEFAULT '0',
 account_type varchar(32) NOT NULL DEFAULT '',
 verified tinyint NOT NULL DEFAULT '0',
 allow_mail tinyint unsigned NOT NULL DEFAULT '0',
 parent_account int unsigned NOT NULL DEFAULT '0',
 closest_airport varchar(3) NOT NULL DEFAULT '',
 PRIMARY KEY (id),
 UNIQUE KEY email (email),
 KEY country_id (country_id),
 KEY state_id (state_id)
) ENGINE=InnoDB
```

This table shows the QPS of indexing one million rows of the above table
and performance for `SELECT`s. By Indexing both `state_id` and
`state_id_2`, performance for selecting each row specifically drops a
bit with the double index but is mainly negligible.

|         | state_id only | state_id_2 only | Both state_id and state_id_2 |
| ------- | ------------- | --------------- | ---------------------------- |
| Query 1 | 108.55        | 100.33          | 107.97                       |
| Query 2 | 12.12         | 28.04           | 28.0                         |

However, having a bigger index slows insertion speed quite a bit:

|                                        | state_id only | Both state_id and state_id_2 |
| -------------------------------------- | ------------- | ---------------------------- |
| InnoDB, enough memory for both indexes | 80 seconds    | 136 seconds                  |

In MySQL 8.0, there's a new `invisible index` feature which will
disregard indexes for queries. If you find queries are `EXPLAIN`ed the
same with or without an index, you can remove it.

## Unused Indexes

Some indexes are just plain unused. Get rid of them with
`performance_schema` and `sys.

```sql
SELECT * from sys.schema_unused_indexes;
+---------------+---------------+-----------------------------+
| object_schema | object_name   | index_name                  |
+---------------+---------------+-----------------------------+
| sakila        | actor         | idx_actor_last_name         |
| sakila        | address       | idx_fk_city_id              |
| sakila        | address       | idx_location                |
| sakila        | payment       | fk_payment_rental           |
.. trimmed for brevity ..
```

## Index and Table Maintenance

The three goals of table maintenance are:

1. Finding and Fixing Corruption
2. Maintaining accurate Index statistics
3. Reducing Fragmentation

### Finding and Repairing Table Corruption

Tables can be corrupted due to hardware or internal bugs.

Corrupted indexes can return incorrect results on queries, or raise
duplicate-key errors when there is no duplicated value.

`CHECK TABLE` can try to guess if the table is corrupt.

As well, `REPAIR TABLE` can work, or an `ALTER TABLE table ENGINE=INNODB`
to reload the table with the current engine.

As well, you could dump the data and reload it.

### Updating Index Statistics

The storage engine provides the optimizer with fuzzy data about the
number of rows a query might examine. The optimizer uses this data
(Index Statistics) to make guesses and generate a query plan. This data
can be out of sync if lots of updates have been made to a table. If so,
you can `ANALYZE TABLE` to regenerate the statistics.

### Reducing Index and Data Fragmentation

B-Trees can become fragmented. To defragment data, run `OPTIMIZE TABLE`,
or dump and reload the table. As well, you can
`ALTER TABLE table ENGINE=INNODB` as well.

Prev: [schema-design-and-management](schema-design-and-management.md)
Next: [query-performance-optimization](query-performance-optimization.md)
