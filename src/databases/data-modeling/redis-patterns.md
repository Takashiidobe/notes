# Redis Data Modeling

## One-to-One Relationships

In a relational database, for optional data, you would use a separate
table:

| product_id | name     | price |
|------------|----------|-------|
| 1          | "Shirt"  | $10   |
| 2          | "Jeans"  | $20   |
| 3          | "Jacket" | $30   |

| product_id | size | section |
|------------|------|---------|
| 1          | S    | Women's |
| 2          | M    | Men's   |
| 3          | L    | Front   |

In a NoSQL database, you can embed all the data in one table, since you
can nest the data in a field and ignore it when unnecessary.

## One-to-Many Relationships

If you have a collection that is bounded, you can embed the data into
the table. However, for unbounded data, you want to make a new table and
select into it when necessary.

## Many-to-Many Relationships

If both sides of the table are bounded, you can embed the join keys for
both sides in a JSON field, for example.

If only one side is unbounded, you can embed the bounded side into the
table.

If both sides are unbounded, use a join table as in SQL.

## The Aggregate Pattern

The aggregate pattern reduces overhead at read time by updating
aggregate information during writes.

## The Polymorphic Pattern

In an RDBMS, you can only store data that has the same-ish columns. In
redis you can store polymorphic data with unique fields in the same
table, only querying what you need and leaving the rest null, avoiding
joins.

## The Bucket Pattern

Turn Redis into a time series database by bucketing your data (reducing
memory usage).

## Trees and Graphs

Redis can model trees and graphs using the cypher language (from Neo4j).

## Schema Version Pattern

You can version your data in each table to allow for less painful
migrations, although that means that all your data is not on the same
version, which makes application code more painful to maintain.

