---
title: "Query Performance Optimization"
---

# Query Performance Optimization

Prev: [indexing-for-high-performance](indexing-for-high-performance.md)
Next: [replication](replication.md)

## Why are Queries Slow?

Queries can be slow in many ways:

1. CPU usage
2. Statistics
3. Locking
4. Fetching Data

Let's start optimizing queries looking at that:

## Slow Query Basics: Optimize Data Access

The most fundamental way a query can be slow is if it analyzes too much
data. To fix that:

1. Find out whether your application is retrieving too much data (either
   too many rows or columns)
2. Find out if MySQL is looking at too many rows.

### Are You Asking the Database for Data You Don't Need?

Here's a few typical mistakes

1. Fetching more rows than needed.

The most common mistake: MySQL data fetching is not lazy. It fetches all
the data requested in the query, thus, if you ask for 100 rows but only
use 10, consider only querying for 10 rows.

2. Fetching all columns from a multitable join

Instead of fetching all columns on a multitable join like this:

```sql
SELECT * FROM sakila.actor
INNER JOIN sakila.film_actor USING(actor_id)
INNER JOIN sakila.film USING(film_id)
WHERE sakila.film.title = 'Academy Dinosaur';
```

Instead, write this, which only fetches data from `sakila.actor`.

```sql
SELECT sakila.actor.* FROM sakila.actor...;
```

3. Fetching all columns

`SELECT *` should raise alarm bells. It's very rare that you need all
columns on a table, and is mainly wasteful.

4. Fetching the same data repeatedly

If you're not careful, an application might fetch the same infrequently
changing data. Instead of doing this, cache it on the application side.

### Is MySQL Examining too much Data?

After only fetching the data required, we can optimize the data while
generating results.

MySQL has a set of query cost metrics:

1. Response Time
2. Number of rows examined
3. Number of rows returned

#### Response Time

Response time is divided into two parts: `Service Time` and `Queue Time`. Queue time is the time waiting, and service time is the time
mysql spent to execute the query.

Calculate a QUBE (quick upper-bound estimate) of query response time
given the queries here to figure out if the query can run any faster.

#### Rows examined and rows returned

You should examine somewhere in the ballpark of the rows you want to
return per query. While it's impossible to have a 1:1 ratio of these,
strive for 1:1 - 10:1. If you're looking at hundreds of rows and only
returning one, it's time to optimize the query, either by indexing or
arranging the table data in a better fashion.

#### Rows examined and access types

You should have an idea of the types of accesses which are illustrated
by `EXPLAIN`.

Here are some examples, in order of fastest access type to slowest.

1. const
   The table has at most one matching row.
2. eq_ref
   One row is read from this table for each combination of rows from the
   previous table. `eq_ref` can be used for indexed columns that are
   compared using the `=` operator, and are `UNIQUE` and `NOT NULL`
   indexes.
3. ref
   All rows with matching index values are read from this table for each
   combination of rows from the previous tables. `ref` is used if the
   join uses the leftmost prefix of the key, or the key is not `UNIQUE`
   in some fashion. This is good if there are only a few matching rows.
4. fulltext
   This uses a fulltext index
5. ref_or_null
   The join type of `ref`, but with NULLS included.
6. Index Merge
   A few indexes are used in tandem to index the result of this query.
7. Unique Subquery
   for queries of the form `value IN (SELECT primary_key FROM single_table WHERE some_expr)`
   that are unique, this replaces the subquery for efficiency.
8. Index Subquery
   Like Unique Subquery, but replaces subqueries that are nonunique.
9. Range
   Only rows that are in a given range are retrieved, using an index.
   Range can be used with `=`, `<>`, `>`, `>=`, `<`, `<=`, `IS NULL`, `<=>`, `BETWEEN`, `LIKE`, `IN()`.
10. Index
    This scans the entire index tree.
11. All
    A full table scan for each combination of rows from the previous
    tables is done.

Take this query for example:

```sql
SELECT * FROM sakilafilm_actor WHERE film_id = 1;
mysql> EXPLAIN SELECT * FROM sakila.film_actor WHERE film_id = 1\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: film_actor
 partitions: NULL
 type: ref
 possible_keys: idx_fk_film_id
 key: idx_fk_film_id
 key_len: 2
 ref: const
 rows: 10
 filtered: 100.00
 Extra: NULL
```

Explain shows that MySQL estimated it needed to access only 10 rows, and
this was a `ref` query, which was pretty good.

If the index is dropped:

```sql
mysql> ALTER TABLE sakila.film_actor DROP FOREIGN KEY fk_film_actor_film;
mysql> ALTER TABLE sakila.film_actor DROP KEY idx_fk_film_id;
mysql> EXPLAIN SELECT * FROM sakila.film_actor WHERE film_id = 1\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: film_actor
 partitions: NULL
 type: ALL
 possible_keys: NULL
 key: NULL
 key_len: NULL
 ref: NULL
 rows: 5462
 filtered: 10.00
 Extra: Using where
1 row in set, 1 warning (0.00 sec)
```

MySQL scans 5462 rows, and has to scan all rows to satisfy this query.

MySQL can apply a where clause in three ways, from best to worst:

1. Apply the condition to the index lookup operation
2. Use a covering index
3. Retrieve all rows then filter out nonmatching rows

However, not all queries can be indexed this easily, and `COUNT`s are a
good example of that:

```sql
mysql> EXPLAIN SELECT actor_id, COUNT(*)
    -> FROM sakila.film_actor GROUP BY actor_id\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: film_actor
 partitions: NULL
 type: index
 possible_keys: PRIMARY
 key: PRIMARY
 key_len: 4
 ref: NULL
 rows: 5462
 filtered: 100.00
 Extra: Using index
```

## Ways to Restructure Queries

Sometimes you can transform queries into equivalent forms to get better
performance while scanning less data.

### Complex Queries Versus Many Queries

Historically it was better to have complex queries instead of simpler
ones due to network overhead, but these days that's not true. Most of
the time simpler queries will suffice.

### Chopping Up a Query

Instead of trying to scan a large segment of data and delete it like
this query:

```sql
DELETE FROM messages
WHERE created < DATE_SUB(NOW(),INTERVAL 3 MONTH);
```

You can try and process fewer rows at a time:

```sql
rows_affected = 0
do {
 rows_affected = do_query(
 "DELETE FROM messages WHERE created < DATE_SUB(NOW(),INTERVAL 3 MONTH)
 LIMIT 10000")
} while rows_affected > 0
```

### Join Decomposition

While JOINs are the preferred way of accessing data:

```sql
SELECT * FROM tag
JOIN tag_post ON tag_post.tag_id=tag.id
JOIN post ON tag_post.post_id=post.id
WHERE tag.tag='mysql';
```

This might be faster, even though you have to scan more lines.

```sql
SELECT * FROM tag WHERE tag='mysql';
SELECT * FROM tag_post WHERE tag_id=1234;
SELECT * FROM post WHERE post.id in (123,456,567,9098,8904);
```

Prev: [indexing-for-high-performance](indexing-for-high-performance.md)
Next: [replication](replication.md)
