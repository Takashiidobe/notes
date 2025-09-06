---
title: ParadeDB
date created: Tuesday, July 22nd 2025, 7:23:58 pm
date modified: Wednesday, July 23rd 2025, 7:17:29 am
---

# ParadeDB

- Tokenization: splitting text into searchable chunks
- Stemming: reducing words to root, e.g. running -> run
- inverted indexes: data structure for full text search
- Aggregation: statistics over a dataset, counts, sums, averages
- Facet: Aggregation over full text search
- Elastic DSL: DSL used by elastic to search

ParadeDB: Elasticsearch alternative built on Postgres:

- pg_search: Full text search with BM25
- pg_analytics: Read data lakes (S3) and table formats (iceberg)

# Why Migrate?

- Data reliability
- Freshness
- No schema changes
- Fast reindexing in update-heavy scenarios

## What is Full Text Search?

Query documents by presence of keywords or phases
Simple or Complex
- Indexing: Tokenize and store text in an inverted index
- Querying: Finding text in the index that matches a query

## Full Text Search in Postgres

Beforehand:

- LIKE operator
- ts_vector/ts_rank + GIN index
- pg_tgrm (pg_trigram)

`ts_vector` stores the tokenized, stemmed representation of text.
`ts_rank` lets you rank them using TF_IDF.
`GIN indexes` are an inverted index of `ts_vector` columns, improving query performance.

`pg_tgrm`turns text into trigrams, so cheese -> (che, hee, ees, ese).

## What is Postgres FTS Missing?

- BM25 Relevance (Best match 25), kinda like TF-IDF that considers relevance of documents
- More powerful tokenizers and token filters
- Elastic DSL search
- Fast facets and aggregations

## BM25

Improvement on the TF-IDF algorithm

1. Longer documents have more terms, but these aren't necessarily more relevant. BM25 takes care of document length.
2. More common words are considered less important.

## What is pg_search

- Rust extension that uses Tantivy to add FTS to postgres.
- Tantivy is a FTS library in rust with inverted indexes and columnar storage

## Tantivy is Fast

- Immutable segment-based design
- Mmapped files for fast I/O
- Rust and SIMD

## How pg_search is Build

- Custom FTS operator `@@@`
- Custom postgres index
- Query builder API
- custom scan

```sql
SELECT * from mock_items WHERE id < 10 AND description @@@ 'keyboard'; -- searches for keyboards
```

## Custom Index

- It's a BM25 index on any text field. It's also meant to be covering, so over multiple columns.

### Query Builder API

- Queries can use the query builder API:

```sql
SELECT * FROM mock_items WHERE id => paradedb.boolean(
	should => ARRAY[
	paradedb.boost(query => paradedb.parse('description:shoes'), boost => 2.0), paradedb.term(field => 'description', value => 'running)
	]
);
```

### Custom Scan

- Allows for 3 optimizations for FTS
- Predicate pushdown
- BM25 scoring
- Fast facets + aggregations

### Predicate Pushdown

- `SELECT * from mock_items WHERE description @@@ 'keyboard' AND rating < 5`.
- Without a custom scan, postgres performs separate scans over description and rating, even if these are both indexed

### Scoring Projection

`SELECT * FROM mock_items WHERE description @@@ 'keyboard'` lets you project a score column into the result

### Facets Are Slow

- Tantivy has fast fields, which is columnar storage, so postgres can do visibility checking on batches

- Even faster facets with DataFusion