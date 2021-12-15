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

## Query Execution Basics

Remember how MySQL interprets queries:

1. The server parses the SQL statement
2. The server turns that into a query execution plan
3. The query execution engine executes the plan
4. The server sends the result to the client

### The MySQL Client/Server Protocol

The MySQL client/server protocol is half-duplex, which means it can be
sending or receiving messages, but not both.

This makes it so messages cannot be canceled, and is like grabbing a
lock: if the client makes a request, it must read to the end of the
server's message before responding.

### Query States

Each MySQL connection or thread has a state that shows what it is doing
at any given time.

These can be queried by the `SHOW FULL PROCESSLIST` command.

1. Sleep
   The thread is waiting for a query
2. Query
   The thread is executing the query or sending the result back to the
   client
3. Locked
   The thread is waiting for a table lock. Row locks do not cause the
   thread to enter the Locked state.
4. Analyzing and statistics
   The thread is checking storage engine statistics and optimizing the
   query.
5. Copying to tmp table [on disk]
   The thread is processing the query and copying results to a temporary
   table. If the state ends with `on disk`, MySQL is converting an
   in-memory table to an on-disk table.
6. Sorting result
   The thread is sorting a result set.

### The Query Optimization Process

There are many steps that might be combined, but lets look at these one
by one:

#### The Parser and the Preprocessor

MySQL's parser breaks the query into tokens and builds a parse tree from
them. It also ensures that the tokens in the query are valid and in the
proper order.

Afterwards, the preprocessor checks to make sure the referenced tables
and columns exist, and that column references aren't ambiguous.

Finally, it checks privileges to make sure the user can access the data
it's querying for.

#### The Query Optimizer

Once the parse tree is valid, the optimizer tries to find the best query
execution plan to execute.

MySQL uses a cost-based optimizer, which used to have a unit of cost of
a random 4KB data page read, referring to statistics.

You can query the last statement executed's cost like so:

```sql
mysql> SELECT SQL_NO_CACHE COUNT(*) FROM sakila.film_actor;
+----------+
| count(*) |
+----------+
|     5462 |
+----------+

mysql> SHOW STATUS LIKE 'Last_query_cost';
+-----------------+-------------+
| Variable_name   | Value       |
+-----------------+-------------+
| Last_query_cost | 1040.599000 |
+-----------------+-------------+
```

This query means the optimizer guesses that it will make 1040 random
page reads to execute the query, based on statistics.

The optimizer might not always choose the best plan because:

1. Statistics could be inaccurate. The storage engine could have
   outdated statistics.
2. The cost metric is not equivalent, because MySQL assumes that each
   page read is random and on-disk. The reads could be sequential (in
   this case, they probably are) and the pages could be cached in memory
   if the query was recently run.
3. MySQL wants the fewest page reads, while you probably want the
   shortest query execution time. These can be different.
4. MySQL doesn't always do cost-based optimization. For example, for a
   full text operation like `MATCH()`, it'll always use a `FULLTEXT`
   index.
5. The optimizer doesn't take into account the cost of operations like
   stored functions or user-defined functions.
6. The optimizer doesn't estimate every possible execution plan, so it
   might miss an optimal plan.

MySQL can execute `static` or `dynamic` optimizations:

`Static` optimizations involve transforming queries to other ones using
algebraic query rules.

`Dynamic` optimizations happen at runtime, and include:

1. Reordering Joins
   Tables don't have to be joined in the order specified in the query.
   The Optimizer might reorder these for better performance.
2. Converting `OUTER JOIN`s to `INNER JOIN`s
   `INNER JOIN`s are cheaper than `OUTER JOIN`s and in some cases they
   might be reordered for performance.
3. Applying algebraic equivalence rules
   This does constant optimizations, like changing `5 = 5` and `a > 5`
   to just `a > 5`.
4. `COUNT()`, `MIN()`, `MAX()` optimizations
   These operations can be optimized away by NULL conditions and
   indexes (the min is the leftmost item on a B-TREE index) and (the
   max is the rightmost). This wlll be noted in the `Select tables optimized away` in the `EXPLAIN` plan.`
5. Evaluating and Reducing constant expressions
   If MySQL can reduce an expression to a constant, it will. A `MIN()`
   can be reduced to a primary key lookup on an index. Or if a WHERE is
   evaluated once, it can be set to a constant for other parts of the
   query.
6. Covering Indexes
   MySQL can use an index to avoid reading rows when the index has a ll
   the columns a query needs.
7. Subquery Optimization
   MySQL can convert subqueries into more efficient alternative forms.
8. Early Termination
   MySQL can stop processing a query or a step in a query as soon as it
   fulfills a query or step, like for `LIMIT` queries. As well, it can
   abort if it finds an impossible condition, like comparing a negative
   number with an unsigned primary key.
9. Equality Propagation
   MySQL recognizes when a query holds two equal columns and then
   propagates `WHERE` clauses across equivalent columns.
10. `IN()` list comparisons
    In MySQL, values in a `IN()` are sorted and then binary searched
    for lookup. This makes checking for items in an `IN()` faster.

#### Table and Index Statistics

The MySQL query optimizer has to ask engines for statistics on the
tables in query: The optimizer uses this information to generate
execution plans.

#### MySQL's join execution strategy

MySQL used to use a Nested loop join strategy for joins: It would loop
through the first table, finding all matching rows, then process the
next join by using the matching rows from the previous query, continuing
on. In MySQL 8.0.20, MySQL started using `hash joins` instead for speed.

#### The execution plan

MySQL doesn't generate bytecode to execute a query, instead, it creates
a generated tree. The final plan contains enough information to
reconstruct the original query. You can see this by running `EXPLAIN FORMAT=TREE` before your statement, or `EXPLAIN EXTENDED` followed by
`SHOW WARNINGS`.

#### The join optimizer

It is often possible to join the tables in several different orders and
get the same results.

Take this query:

```sql
SELECT film.film_id, film.title, film.release_year, actor.actor_id,
actor.first_name, actor.last_name
FROM sakila.film
INNER JOIN sakila.film_actor USING(film_id)
INNER JOIN sakila.actor USING(actor_id);
```

This query joins from `film` -> `film_actor` -> `actor`. If we explain
the query though, it goes in reverse, `actor` -> `film_actor` -> `film`.

```sql
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: actor
 partitions: NULL
 type: ALL
 possible_keys: PRIMARY
 key: NULL
 key_len: NULL
 ref: NULL
 rows: 200
 filtered: 100.00
 Extra: NULL
*************************** 2. row ***************************
 id: 1
 select_type: SIMPLE
 table: film_actor
 partitions: NULL
 type: ref
 possible_keys: PRIMARY,idx_fk_film_id
 key: PRIMARY
 key_len: 2
 ref: sakila.actor.actor_id
 rows: 27
 filtered: 100.00
 Extra: Using index
*************************** 3. row ***************************
 id: 1
 select_type: SIMPLE
 table: film
 partitions: NULL
 type: eq_ref
 possible_keys: PRIMARY
 key: PRIMARY
 key_len: 2
 ref: sakila.film_actor.film_id
 rows: 1
 filtered: 100.00
 Extra: NULL
```

Let's see what would happen if we forced MySQL to use our optimization
with the `STRAIGHT_JOIN` keyword:

```sql
ysql> EXPLAIN SELECT STRAIGHT_JOIN film.film_id...\G
*************************** 1. row ***************************
 id: 1
 select_type: SIMPLE
 table: film
 partitions: NULL
 type: ALL
 possible_keys: PRIMARY
 key: NULL
 key_len: NULL
 ref: NULL
 rows: 1000
 filtered: 100.00
 Extra: NULL
*************************** 2. row ***************************
 id: 1
 select_type: SIMPLE
 table: film_actor
 partitions: NULL
 type: ref
 possible_keys: PRIMARY,idx_fk_film_id
 key: idx_fk_film_id
 key_len: 2
 ref: sakila.film.film_id
 rows: 5
 filtered: 100.00
 Extra: Using index
*************************** 3. row ***************************
 id: 1
 select_type: SIMPLE
 table: actor
 partitions: NULL
 type: eq_ref
 possible_keys: PRIMARY
 key: PRIMARY
 key_len: 2
 ref: sakila.film_actor.actor_id
 rows: 1
 filtered: 100.00
 Extra: NULL
```

The previous query plan would've looked at fewer rows in the first
table, (200 vs 1000) having a lower cost for later queries.

Unfortunately, a join over `n` tables costs you `O(n!)` operations, so
MySQL uses greedy search to try to find the best query.

Also note that some queries can't be reordered, which lowers the amount
of optimizations MySQL needs to look for.

#### Sort optimizations

If MySQL can't use an index to produce a sorted result, it must sort the
rows itself. If done in memory, it does quicksort, otherwise it does an
on disk mergesort.

Previously, MySQL used to use a `two pass` algorithm for reading row
pointers, but nowadays it does a `single pass` algorithm for the same.

Filesorts take a long time and use a lot of space on disk, which can be
problematic.

### The Query Execution Engine

The Query execution stage isn't that complex: MySQL follows the
instructions in the query execution plan. Think of it like assembly,
where the storage engines have to implement only a few instructions, and
can generate much more instructions off those building blocks.

### Returning Results to the Client

Finally, the server generates and sends results incrementally to the
client in chunks. Each row is sent in a separate packer in the MySQL
client/server protocol, and buffered at the TCP protocol layer.

## Limitations of the MySQL Query Optimizer

Given all these optimizations, there are a few limitations:

### Union Limitations

MySQL sometimes can't push down conditions from outside a `UNION` to the
inside, where they can enable better results.

Take this query, which should only need to store 20 rows from both
tables (but it doesn't, it stores all the rows in each subquery).

```sql
(SELECT first_name, last_name
 FROM sakila.actor
 ORDER BY last_name)
UNION ALL
(SELECT first_name, last_name
 FROM sakila.customer
 ORDER BY last_name)
LIMIT 20;
```

This can be fixed by redundantly adding a `LIMIT 20` to both clauses:

```sql
(SELECT first_name, last_name
 FROM sakila.actor
 ORDER BY last_name
 LIMIT 20)
UNION ALL
(SELECT first_name, last_name
 FROM sakila.customer
 ORDER BY last_name
 LIMIT 20)
LIMIT 20;
```

Now the temporary tables will only contain 40 rows, but they aren't
ordered. Add an Order By in both tables for consistent results.

### Equality Propagation

The optimizer can also miss equality propagation: For a huge `IN()` on a
column, the optimizer will share the list by copying it to the
corresponding columns. This can slow optimization and execution.

### Parallel Execution

MySQL can't execute a single query in parallel.

### SELECT and UPDATE on the Same Table

MySQL doesn't let you SELECT from a table, while running an `UPDATE` on
it.

```sql
mysql> UPDATE tbl AS outer_tbl
    -> SET c = (
    -> SELECT count(*) FROM tbl AS inner_tbl
    -> WHERE inner_tbl.type = outer_tbl.type
    -> );
ERROR 1093 (HY000): You can't specify target table 'outer_tbl'
for update in FROM clause
```

To work around this, you can use a derived table, because MySQL
materializes it as a temporary table.

```sql
mysql> UPDATE tbl
    -> INNER JOIN(
    -> SELECT type, count(*) AS c
    -> FROM tbl
    -> GROUP BY type
    -> ) AS der USING(type)
    -> SET tbl.c = der.c;
```

## Optimizing Specific Types of Queries

The below are some common queries to optimize:

### Optimizing `COUNT()` queries

The `COUNT()` aggregate function is extremely misunderstood and the
source of many woes.

#### What `COUNT()` does

`COUNT()` is a special function that counts `values` and `rows`. If a
column name or other expression is specified, `COUNT()` counts how many
times that expression has a value.

Otherwise, `COUNT()` counts the number of rows in the result. `COUNT(*)`
is a special form of `COUNT()` which just counts the number of rows.

#### Simple Optimizations

You can use COUNT to count multiple values at the same time:

```sql
SELECT COUNT(color = 'blue' OR NULL) AS blue, COUNT(color = 'red' OR NULL)
AS red FROM items;
```

#### Using an Approximation

If you don't need an accurate count, you can use an approximation: This
can be done by querying the `EXPLAIN` query instead of the real query.

### More complex optimizations

There are other optimizations for `COUNT(*)`, like using caching
`memcached` or a covering index.

### Optimizing JOIN queries

To Optimize `JOIN`s:

1. Make sure there are indexes on the columns in `ON` or `USING`
   clauses. In general, indexes only need to be added on the second
   table in the join order.
2. Try to ensure that `GROUP BY` or `ORDER BY` refers only to columns
   from a single table, so `MYSQL` can try to use an index for that
   operation.
3. Be careful upgrading MySQL, because this can invalidate `JOIN`
   syntax.

### Optimizing GROUP BY with ROLLUP

`GROUP BY`s that do a lot of aggregation can be optimized by `WITH ROLLUP`.

### Optimizing LIMIT and OFFSET

Queries with `LIMIT`s and `OFFSET`s are common in systems that use
pagination. This needs to be indexed, otherwise performance will be very
poor.

A common problem is having a high value for the offset:

For a query that has `LIMIT 10000, 20` (LIMIT 10000, OFFSET 20), it
generates 10,020 rows and throws away 10000 of them. This is very
expensive.

To optimize this, do the offset on a covering index, instead of the full
rows.

A deferred join can be used to optimize this:

```sql
SELECT film.film_id, film.description
FROM sakila.film
INNER JOIN (
SELECT film_id FROM sakila.film
ORDER BY title LIMIT 50, 5
) AS lim USING(film_id);
```

Otherwise, cursor pagination can be done to query for fewer rows:

To grab the first page:

```sql
SELECT * FROM sakila.rental
ORDER BY rental_id DESC LIMIT 20
```

To grab any further rows:

```sql
SELECT * FROM sakila.rental
WHERE rental_id < 16030
ORDER BY rental_id DESC LIMIT 20;
```

### Optimizing `SQL_CALC_FOUND_ROWS`

`SQL_CALC_FOUND_ROWS` is used to see if there would be a next page of
results. Instead of doing that, which generates all the rows it would've
found, we can use `EXPLAIN` to find out the length of the result set.

### Optimizing UNION

MySQL always executes `UNION` queries by creating a temporary table and
then moving on with the rest of the query. Try to use `UNION ALL` unless
you need to server to eliminate duplicate rows. `UNION ALL` doesn't
eliminate the temporary table, but it doesn't do a `DISTINCT` count.

Prev: [indexing-for-high-performance](indexing-for-high-performance.md)
Next: [replication](replication.md)
