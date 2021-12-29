---
title: core-concepts-in-dynamodb
---

# Core Concepts in DynamoDB

Prev: [what-is-dynamodb](what-is-dynamodb.md)
Next: [advanced-concepts](advanced-concepts.md)

## Five Basic concepts

1. tables (can house multiple entity types)
2. items (a record in a table)
3. attributes (the columns of an item, which can be the following):

- Scalars (string, number, binary, boolean, null)
- Complex (lists and maps)
- Sets (strings, numbers, binary)

4. Primary keys (simple or composite, i.e. multiple columns)
5. Secondary Indexes

## Primary Keys and Secondary Indexes

### Primary Keys

There are either `simple` or `composite` primary keys.

A simple primary key consists of a single element, called a partition
key.

A composite primary key consists of a partition key and a sort key.

A simple primary key is useful for fetching a single item at a time.

A composite primary key lets you fetch many -- you can grab all items by
a partition key, and further sort on the sort key.

### Secondary Indexes

There are two kinds of Secondary Indexes, Local and Global.

Local secondary indexes use the same partition key as your table's
primary key, but a different sort key.

Global secondary indexes can index any attributes you want for partition
and sort key.

Local secondary indexes can be strongly consistent, but global secondary
indexes can only be eventually consistent.

## Item collections

An item collection is a group of items that share the same partition key
in either the base table or a secondary index.

Prev: [what-is-dynamodb](what-is-dynamodb.md)
Next: [advanced-concepts](advanced-concepts.md)
