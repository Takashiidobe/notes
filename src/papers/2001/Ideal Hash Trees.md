---
title: Ideal Hash Trees
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 20th 2025, 10:51:11 am
pdf_url: "[[Ideal Hash trees.pdf]]"
author:
  - Phil Bagwell
---

# Ideal Hash Trees

This paper describes "Hash Array Mapped Tries", aka "HAMTs". It involves
using an Array Mapped Trie as a backing store and extending it to work
as a Hash table.

## Essentials

The HAMT is a 32-pointer tree that uses hashes to place items in the
correct location in the trie. The requirement for a HAMT is a fast count
population algorithm (counting the number of 1s in a bitset).

The HAMT uses 2 32-bit integers -- one integer is used to represent the
existence of 32 possible arcs, with a 1 meaning a valid arc, and a 0 to
mean an invalid arc. The other integer is used to store a pointer to the
location in memory where the trie lives.

# Ideal Hashing

The HAMT uses a hash function to generate an array index prefix, which
is used to find an empty slot in the HAMT to insert the key, value pair
into. There is a root hash table which can house either a key-value
pair, or another sub-hash table.

| Map | Base    | Key | Value   | Key | Value |
|-----|---------|-----|---------|-----|-------|
| Key | Value   |     |         |     |       |
| Map | Base -> | Key | Value   |     |       |
| Key | Value   |     |         |     |       |
| Map | Base -> | Map | Base -> | Key | Value |
| Key | Value   |     |         | Key | Value |


## Search for a Key

To search for a key, compute the 32-bit hash for the key, take the 5
most significant bits and use them as an integer to index into the root
hash table.

There are 3 possible cases.

1. The entry is not in the table.
2. The entry is a key value pair and the key either matches the desired
   key or not.
3. The entry has a 32-bit map sub-hash table and a sub-trie pointer that
   points to an ordered list of non-empty sub-hash table entries.

We then take the next 5 bits of the hash and use them as an integer to
index into the bit map. If the bit is 0, the hash table is empty,
otherwise, repeat the search until a terminating key/value pair is found
or the search fails.

With a 32-bit perfect random hash, and a depth of 5, the key hash will
uniquely define a terminal node after log(N) bits. This search cost can
be lowered to O(1).

## Insertion

The initial steps required to add a key is the same as search. If an
empty position is discovered in the hash table or a sub-hash table is
found, the new key-value pair is substituted for the empty position. 

In a sub-hash table, the new bit is added to the bit map and the table
is increased by one in size, with a new hash table being allocated, the
existing table copied to it, added in, and the old one being freed.

If the key collides with an existing one, the existing key is replaced
with a sub-hash table and the next 5 bit hash of the existing key is
computed.

## Pros of HAMTs

The HAMT achieves almost hash table-like speed while being much more
memory efficient. As well, the resizing operation of a HAMT is cheap,
since it resizes dynamically.

As well, all operations can be written in a way to have a constant time
worst case runtime. 
