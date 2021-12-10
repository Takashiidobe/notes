---
title: what-is-dynamodb
---

Next:
[core-concepts-in-dynamodb](core-concepts-in-dynamodb.md)

# What is DynamoDB?

## Five Misconceptions about DynamoDB

1. Dynamodb is just a key-value store.

- Not true, with the plethora of secondary keys and indexes, dynamodb
  can handle complex data models, like Github's.

2. DynamoDB doesn't scale.

- It's used for Amazon web services. It's true that scans and single
  partitions don't scale, but you shouldn't use either.

3. DynamoDB is only for enormous scale.

- It works well for any kind of scale, with easy provisioning, simple
  billing, and HTTP API.

4. You can't use DynamoDB if your data model will change.

- You must know your access patterns up front. If you don't know how the
  data will be queried, you can't create model that will be fast when
  modeling.

5. You don’t need a schema when using DynamoDB.

- DynamoDB won't enforce a schema like a relational database, but pushes
  that concern to the application-level. You still need a schema.

## Key Properties of DynamoDB

DDB is a Key-Value or wide-column data model. For simple access patterns,
Key-Value shines, since you get constant time access for any one record
in the table.

In a wide-column store, each record in the hash table is a B-tree. This
allows for fast range queries.

The HTTP connection model (compared to the TCP model found in MySQL and
Postgres) allow you to avoid creating a connection pool to begin
querying.

IAM allows for convenient management and dovetails into being
Infrastructure as code friendly.

RCUs and WCUs can be scaled up independently, compared to with a
traditional database, where they both are bought in tandem (more RAM,
more disk space). You can also start out with On-Demand Pricing to learn
about your usage, or to handle spiky workloads, before allocating a set
amount of RCUs and WCUs.

DynamoDB streams allows you to read a transactional log of each write
transaction in a DynamoDB table.

It's fully managed, which lowers overhead on maintenance, which
managed databases have a lot of.

## When to use DynamoDB

1. hyper-scale applications
2. hyper-ephemeral compute

### Hyperscale

RDBMS made sense to conserve on storage. Data would be written once, in
a normalized format. But the pricing of disk went down drastically, from
200,000 per GB in 1980 to 0.03 per GB in 2014.

In 2004, Amazon built "Dynamo" to deal with hyperscale for their own
databases.

Their reasons for creating dynamo were:

Inability to use advanced relational features at scale: 70% of their
operations operated on a single record, and 20% would return multiple
rows in the same table. Thus, 90% of queries didn't use joins.

Consistency was expensive: for Amazon, consistency wasn't as important
as availability. This let dynamo scale performance in exchange for a bit
of correctness.

### Hyper-ephemeral compute (serverless)

AWS Lambda popularized the notion of event-driven compute. By moving
from a model where hardware needed to be allocated to a model where code
would run on demand, and dynamodb pairs well with that.

### Other situations

- Most OLTP applications: Good for online, transactional processing
  applications.
- Caching: DynamoDB can be used as a cache to store the results of
  complex, frequently-accessed queries from other databases.
- Simple data models: DynamoDB is a great fit for mainly key-value
  lookups.

## Comparisons to other databases

1. Relational databases
2. MongoDB
3. Apache Cassandra

### DynamoDB vs Relational

1. You lose relational features like transactions.
2. More people know relational databases.

### DynamoDB vs MongoDB

MongoDB is a document database, which allows for richer querying
patterns after the fact, and lots of index types, like text, geospatial,
and multi-key indexes.

### DynamoDB vs Cassandra

Cassandra is Wide-column store, which dynamodb can take the place of.
But it's hard to beat dynamodb's managed options

Next:
[core-concepts-in-dynamodb](core-concepts-in-dynamodb.md)
