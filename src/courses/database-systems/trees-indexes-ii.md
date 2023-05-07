---
title: "Trees Indexes II"
---

# Trees Indexes II

Prev: [trees-indexes-i](trees-indexes-i.md)
Next: [index-concurrency-control](index-concurrency-control.md)

## Additional Index Usage

**Implicit Indexes**: Most DBMS' will create an index to enforce integrity constraints (primary keys, uniqueness).

**Partial Indexes**: Creates an index on a subset of the entire table. If one value is much more common than the other, this has lots of cost savings.

**Covering Indexes**: All attributes needed to process the query are available in an index. The DBMS can complete the query just by looking at the index itself.

**Index Include Columns**: Embed addition columns in an index to support index-only queries for common queries.

**Function/Expression Indexes**: Store the output of a function or expression as the key instead of the original value.

## Radix Trees

A radix tree is a variant of a trie that examines prefixes one by one instead of comparing the whole key. Nodes are conslidated to represent the largest prefix before keys differ.

The height is bound to the length of the keys instead of the number of keys, but requires that key types can be decomposed into binary comparable digits.

## Inverted Indexes

An inverted index stores a mapping of words to records that contain those words in the target attribute. This is used for full text searching.

**Query Types**:
- Phrase Searches: Find records that contain a list of words in the given order.
- Proximity Searches: Find records where two words occur within n words of each other.
- Wildcard searches: Find records that contain words that match some pattern (.e.g regular expressions).

**Design Decisions**:
- What to store: The index needs to store at least the words contained in each record (separated by punctuation characters). It can include additional information like word frequency, position, and other metadata.

Prev: [trees-indexes-i](trees-indexes-i.md)
Next: [index-concurrency-control](index-concurrency-control.md)
