---
title: "Schema Design and Management"
---

# Schema Design and Management

Prev: [optimizing-server-settings](optimizing-server-settings.md)
Next: [indexing-for-high-performance](indexing-for-high-performance.md)

Schema management is the logical design of the tables you have.

## Choosing Optimal Data Types

1. Smaller is usually better

Smaller data types are faster because they use less space on the disk,
in memory, and in the CPU cache.

2. Simple is Good

Simpler datatypes (like integers) are simpler to compare and cost less
CPU cycles. Strings, for example, are expensive to compare. Store dates
as dates or datetimes for this reason.

3. Avoid `NULL` if possible

`NULL`s are best to be avoided if possible. You should default to `NOT NULL`ing all columns unless you intend to store `NULL` in them. Columns
with `NULL` take up more space in indexes, statistics, and make
comparisons more complicated.

### Whole Numbers

There are five types:

1. TINYINT
2. SMALLINT
3. MEDIUMINT
4. INT
5. BIGINT

Which store 8, 16, 24, 32, 64 bits of data.

Numbers can be `SIGNED` or `UNSIGNED`, unsigned disallowing negative
values and about doubling the allowed space.

### Real Numbers

Here are some real number types. Decimal is for real numbers, and float
and double are for floats respectively.

1. DECIMAL (4 bytes)
2. FLOAT (4 bytes)
3. DOUBLE (8 bytes)

### String Types

#### Varchar

Varchar stores variable-length character strings that require less
storage space than fixed-length types, because they only use as much
space as needed. Varchar uses 1 or 2 extra bytes to record the value's
length. Varchar should be the default, especially when storing UTF-8
strings.

#### Char

Char is a fixed length string. Char is useful for storing very short
strings or if the strings are the same value, since there is no penalty
for variable size.

### BLOB and TEXT types

There are many types for these, but BLOB and TEXT are handled as unique
objects with their own identity.

BLOBs are for binary data with no collation, and TEXT has a character
set and collation.

### Using ENUMs instead of strings

If you have a set number of strings you want to put in a column, use an
ENUM instead. That being said, they're sorted by the order of insertion
(since they're integers), so be careful about that.

### Date and Time Types

DATETIME can hold a large range of values, from the year 1000 to the
year 9999, with a precision of one microsecond. This takes 8 bytes.

TIMESTAMP stores the number of seconds from 1970 GMT. This takes only 4
bytes of storage, but does not persist timezone data.

### Bit-Packed Data Types

Bit-Packed data types are like C++'s Bitset, except stored as a string.
They support the regular operations, like SET, and bitwise operations.

### JSON Data

While JSON data is supported in MySQL 5.7, it uses up more table space
and data than storing it in an SQL table. It is both faster and more
efficient to access sql instead of JSON.

## Choosing Identifiers

Avoid using enums or strings for identifiers, and instead try to go with
integers, since they work with `AUTO INCREMENT`.

## Special Types of Data

- Remember that IPv4 Addresses are 4 Byte integers, so you should
  store them as such.

## Schema Design Gotchas in MySQl

### Too Many Columns

Any table with too many columns that is queried by a Row Based Database
(like MySQL) will have poor performance. Consider breaking up such
tables into logically queried ones.

### Too Many Joins

Joins are very slow on MySQL. Try to avoid joining more than a few
tables at a time.

### The All-Powerful ENUM

Don't abuse ENUM. Think if your ENUMs can be foreign-keyed to a
dictionary or a lookup table instead.

### The ENUM in Disguise

Instead of using a set for some values, consider using an ENUM.

### NULL Not Invented Here

Don't be afraid of using NULL when necessary. Don't use a magic int (-1)
or an invalid datetime, when you could just use NULL instead.

## Schema Management

Schema Management is one of the most common tasks of a DBA, but this can
be a bottleneck.

Use Source Control and CI/CD for schema changes to make sure you can
rollback to a previous version when necessary.

A popular schema management tool is Skeema.

### Running Schema Changes in Production

To Run schema changes in production, you can use tools like `gh-ost` to
run migrations without affecting DDL.

Prev: [optimizing-server-settings](optimizing-server-settings.md)
Next: [indexing-for-high-performance](indexing-for-high-performance.md)
