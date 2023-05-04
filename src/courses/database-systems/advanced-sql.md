---
title: "Advanced SQL"
---

# Advanced SQL

Prev: [course-introduction-and-the-relational-model](course-introduction-and-the-relational-model.md)
Next: [database-storage-i](database-storage-i.md)

## Relational Languages

- Edgar Codd published papers on relational models in the 1970s, but these were math papers.
- The user only needs to specify the result they want using SQL. The DBMS generates an efficient plan to execute it.
- Relational algebra is based on **sets** (unordered, no duplicates). SQL is based on **bags** (unordered, allows duplicates).

## SQL History

Comprised of 3 different classes of commands:

1. Data Manipulation Language (DML): Select, Insert, Update, Delete
2. Data Definition Language (DDL): Schema definition (Create table)
3. Data Control Language (DCL): Security, Access Control

## Aggregates

An aggregation function takes in a bag of tuples as its input and then produces a single scalar value as output.

Count will turn a scalar (the rows of the student table) into one number.

```sql
SELECT COUNT(*) FROM student WHERE login like '%@cs';
```

You can use multiple aggregates within a single `SELECT` statement:

```sql
SELECT AVG(gpa), COUNT(sid) FROM student WHERE login LIKE '%@cs';
```

Or distinct users (if you have duplicates).

```sql
SELECT COUNT(DISTINCT login) FROM student WHERE login LIKE '%@cs';
```

If you want to output an aggregate, use a `HAVING` clause.

```SQL
SELECT AVG(s.gpa) AS avg_gpa, e.cid
FROM enrolled AS e, student AS s
WHERE e.sid = s.sid
GROUP BY e.cid
HAVING avg_gpa > 3.9;
```

## String Operations

The SQL standard says that strings are case sensitive and use single-quotes only.

- Pattern matching is used for `LIKE` or `ILIKE` keywords (insensitive match)
    - "%" matches any substring (including empty).
    - "_" matches any one character.
- Concatenation: "||" will concatenate two or more strings into a single string.

## Output Redirection

- Instead of having the output of a query returned in the terminal, you can store it in another table, for querying later on.

- New Table:

```sql
SELECT DISTINCT cid INTO CourseIds FROM enrolled;
```

- Existing Table (same number of columns + same types required):

```sql
INSERT INTO CourseIds (SELECT DISTINCT cid FROM enrolled);
```

## Output Control

- `ORDER BY` imposes a sort on tuples

```sql
SELECT sid FROM enrolled WHERE cid = '15-721' ORDER BY grade DESC;
```

Multiple `ORDER BY`s can be used to break ties:

```sql
SELECT sid FROM enrolled WHERE cid = '15-721' ORDER BY grade DESC, sid ASC;
```

Any arbitrary expression may be used:

```sql
SELECT sid FROM enrolled WHERE cid = '15-721' ORDER BY UPPER(grade) DESC, sid + 1 ASC;
```

- `LIMIT` imposes a restriction on the number of tuples:

```sql
SELECT sid, name FROM student WHERE login LIKE '%@cs' LIMIT 10;
```

- `OFFSET` allows you to return a range in the results (be careful, as this requires `LIMIT` + `OFFSET` memory.

```sql
SELECT sid, name FROM student WHERE login LIKE '%@cs' LIMIT 10 OFFSET 20;
```

## Nested Queries

- You can invoke queries inside of other queries. Outer queries can access inner queries, but not the other way around.

```sql
SELECT name FROM student WHERE sid IN (SELECT sid FROM enrolled WHERE cid = '15-445');
```

- `ALL` = Must satisfy expression for all rows.
- `ANY` = Must satisfy expression for at least one row.
- `IN` = Equivalent to `=ANY()`.
- `EXISTS` = At least one row is returned.

## Window Functions

- Performs a moving calculation across a set of tuples.
- Functions can use aggregation functions or special window functions:

1. `ROW_NUMBER`: the number of the current row.
2. `RANK`: the order position of the current row.

- Grouping: use `OVER` clause to specify how to group tuples in the window function, and `PARTITION BY` to specify group.

```sql
SELECT cid, sid, ROW_NUMBER() OVER (PARTITION BY cid) FROM enrolled ORDER BY cid;
```

You can also use an `ORDER BY` for deterministic sorting:

```sql
SELECT *, ROW_NUMBER() OVER (ORDER BY cid) FROM enrolled ORDER BY cid;
```

## Common Table Expressions

- CTEs are like temporary tables for just one query.
- The `WITH` clause binds the output of the inner query to a temporary result with that name.

```sql
WITH nums AS (SELECT 1)
SELECT * from nums;
```

You can bind output columns to names before the `AS`:

```sql
WITH nums (one, two) AS (SELECT 1, 2)
SELECT one + two FROM nums;
```

Use the `RECURSIVE` keyword after `WITH` to allow a CTE to reference itself.

- This returns 1 to 10.

```sql
WITH RECURSIVE iterator (counter) AS (
    (SELECT 1)
    UNION
    (SELECT counter + 1 FROM iterator WHERE counter < 10)
)
SELECT * FROM iterator;
```

Prev: [course-introduction-and-the-relational-model](course-introduction-and-the-relational-model.md)
Next: [database-storage-i](database-storage-i.md)
