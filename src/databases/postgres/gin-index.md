---
title: gin-index
---

Index

# GIN Index

A Gin Index is an index structure which stores a set of (key, posting
list) pairs.

This is useful for full-text search (e.g. for a search engine).

GIN allows the following operations:

```sql
contains: value_array @> query_array
overlap: value_array && query_array
contained: value_array <@ query_array
```

and can be created this way:

```sql
create index gin_idx on aa using gin(a);
```

You can set fuzzy search with a GIN index using
`gin_fuzzy_search_limit`.

Limitations:

    No support for multicolumn indices
    Gin doesn't uses scan->kill_prior_tuple & scan->ignore_killed_tuples
    Gin searches entries only by equality matching. This may be improved in future.
    Gin doesn't support full scans of indices.
    Gin doesn't index NULL values.
