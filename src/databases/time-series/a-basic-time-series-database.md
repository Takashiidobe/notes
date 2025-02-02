---
title: a-basic-time-series-database
date created: Sunday, February 2nd 2025, 9:40:05 am
date modified: Sunday, February 2nd 2025, 9:48:37 am
---

A basic time-series database 

A time-series database needs to handle lookup of a large amount of records through timestamps and various tags.

Imagine a record that has the following format:

`<$TIMESTAMP(u64)>:<$TAGS(string:string)[]>:<$VALUE(u64)>`

We want to have access to each record through its timestamps and tags, so:

We create 3 sets of indexes:

1. First, hash the record and put it in a hashmap. Refer to the record via the hash, and only store the hash. This lowers memory usage.
2. Have a hashmap of timestamp to hashes. We use this to keep records in sorted order, and to lookup via time range.
3. Have a hashmap of tag to hashes. We can use this to lookup and find records via tags.

We can then refer to each record through its timestamp, its hash key, or through its tags.

We'll also want to do compression to lower record size. If records come in often, we can store only the first timestamp, and then for each subsequent record, store its delta from the previous timestamp.

That way, each record's timestamp can be much smaller.

As well, each tag/value can be turned into a set of numbered tuples, where there's a separate lookup that handles getting the original values from each tag/value. That way, each tag/value pair can be turned into just one byte at best case, if there's a lot of duplication of tags + values.

However, if tags and/or values can have high cardinality, this approach doesn't save much space.

I implemented a basic tsdb here:

https://github.com/Takashiidobe/tsdb/