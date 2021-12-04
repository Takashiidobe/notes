---
title: hash-index
---

Index

# Hash Indexes

Hash Indexes are generally good in key-value stores, where you want to
check if a value exists in a set. For almost any other case, you\'ll
probably want to use a B-Tree.

Hash Indexes are an index that hashes some key which produces a 32-bit
integer. This integer is then placed inside a bucket, where it resides
until it is queried for.

At some point, a bucket may be split into two, as it has too many
entries. Additional storage is requested by the index, and a bucket is
split into two.

## Performance vs B-Tree Index

![Size of
Indexes](https://hakibenita.com/images/01-postgresql-hash-index.png)

The B-Tree index is smooth, as it increases more incrementally in size.

The Hash Index is like a staircase, it allocates more in size and then
stays at that size until it needs to allocate more.

The size of the indexes before reindexing:

```sql
db= \di+ shorturl*
          Name           │ Type  │ Table    │Size
─────────────────────────┼───────┼──────────┼────────
shorturl_key_btree_index │ index │ shorturl │ 73 MB
shorturl_key_hash_index  │ index │ shorturl │ 37 MB
shorturl_url_btree_index │ index │ shorturl │ 53 MB
shorturl_url_hash_index  │ index │ shorturl │ 36 MB
```

Size after reindexing

```sql
db= REINDEX TABLE shorturl;
REINDEX

db= \di+ shorturl*
          Name           │ Type  │  Table   │ Size
─────────────────────────┼───────┼──────────┼───────
shorturl_key_btree_index │ index │ shorturl │ 56 MB
shorturl_key_hash_index  │ index │ shorturl │ 32 MB
shorturl_url_btree_index │ index │ shorturl │ 41 MB
shorturl_url_hash_index  │ index │ shorturl │ 32 MB
```

Inserting rows to a table indexed by a hash index is about 10% faster on
postgres.

Reads were about 500% faster, though.

That being said, here are some limitations:

Hash indexes cannot be used for unique constraints:

```sql
sdb= CREATE UNIQUE INDEX shorturl_unique_key ON shorturl USING hash(key);
ERROR:  access method "hash" does not support unique indexes
```

Or multiple columns:

```sql
db= CREATE INDEX shorturl_key_and_url ON shorturl USING hash(key, url);
ERROR:  access method "hash" does not support multicolumn indexes
```

Nor sorted indexes:

```sql
db= CREATE INDEX shorturl_sorted_key ON shorturl USING hash(key desc);
ERROR:  access method "hash" does not support ASC/DESC options
```

or cluster a table:

```sql
db= CLUSTER shorturl USING shorturl_url_hash_index;
ERROR:  cannot cluster on index "shorturl_url_hash_index" because access method does not support clustering
```

or range lookups:

```sql
db= EXPLAIN (COSTS OFF) SELECT * FROM shorturl WHERE key BETWEEN '1' AND '2';
                                   QUERY PLAN
────────────────────────────────────────────────────────────────────────────────
Gather
  -> Seq Scan on shorturl
        Filter: ((key >= '1'::text) AND (key <= '2'::text))
```

or `ORDER BY` queries:

```sql
db= EXPLAIN (COSTS OFF) SELECT * FROM shorturl ORDER BY key LIMIT 10;
                   QUERY PLAN
─────────────────────────────────────────────────
 Limit
   ->  Gather Merge
         Workers Planned: 2
         ->  Sort
               Sort Key: key
               ->  Parallel Seq Scan on shorturl
(6 rows)
```
