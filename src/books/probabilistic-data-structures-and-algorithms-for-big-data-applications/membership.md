---
title: membership
---

# Membership

Prev: \[hashing](hashing.md) Next:
\[cardinality](cardinality.md)

A membership problem for a dataset is a task to decide whether some
element belongs to the dataset or not.

For small sets, this is easy. Place into an array, sort, and lookup.
This costs O(n) space to hold the items and O(log n) comparisons to
find.

In some cases, we only want to know that a match was found. Therefore we
can store some signature of the item rather than the whole value.

## Examples

### Safe-browsing

Imagine we\'re developing a web-browser and notice that some URLs are
known to have malware that needs to be blocked.

While the list is small, we can store all unique URLs in a list and
check the list when navigating.

Since there are billions of bad URLs, this won\'t work well for
real-world applications, as the time to index grows linearly with input.

### DNA sequences

One issue in metagenomic studies is to classify sequences as \"novel\"
or belonging to a previously known genome.

We can preprocess the data to execute membership queries, which if
performed efficiently can reduce the complexity of the data.

## Fast Lookup

We can solve lookup with hashing, but this requires O(log n) bits per
hashed element. This can still be too much for large datasets.

## Bloom Filter

The bloom filter was proposed in 1970. It represents a dataset that
supports two operations:

- Adding an element into the set.
- Testing whether an element is in the set.

The bloom filter is a bit array, with length `m`, and a number of
different hash functions, `k`, while the number of expected elements is
`n`.

The hash functions (h) should be independent and uniformly distributed.

When adding a number to the bloom filter, we compute its hash using the
hash function and set each bit if it wasn\'t previously set.

Assume we\'re hashing capitals, using MurmurHash and FNV1a.

The bloom filter starts out unset:

    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

We add `Copenhagen`, which has hash values of (3, 7). We set 3 and 7.

    [0, 0, 0, 1, 0, 0, 0, 1, 0, 0]

Next, we hash `Dublin`, which has values of (1, 3).

We set 1, since 3 is already set.

    [0, 1, 0, 1, 0, 0, 0, 1, 0, 0]

To test if an element x is in the filter, we hash the input and then
check if all bits are set.

If all bits are set, then the element **may exist** in the filter.

Otherwise, the element is **definitely not** in the filter.

Assume we\'re checking an item like \'Mexico City\' which hashes to (1,
7).

In this case, even though we did not add `Mexico City` to the set, the
bloom filter returns true, which denotes that `Mexico City` may be in
the set, a false positive.

Bloom filters give either false positives or positives (the item was in
the set). Thus, for all checks in a bloom filter, we can deduce that the
item **may be** in the set.

### Count unique elements in the filter

We can approximate the number of items in the filter. This is an
approximation (cardinality).

    Input: Bloom filter of length m with k hash functions
    Output: Number of unique elements in the filter
    N = len([i for i in bloom_filter if i == 1])
    if N < k:
      return 0
    if N == k:
      return 1
    if N == m:
      return m / k
    return - (m / k) * ln (1 - N / m)

#### Properties

**False positives are possible**.

Hash Tables can be seen as a Bloom Filter where you use one hash
function.

The ideal false positive rate of 1%, the filter has to be 10 times
longer than the expected number of elements n and use 6 hash functions.

**False negatives are not possible**.

To handle 1 billion elements and key the false positive rate to about
2%, we must use \~ 1GB of memory.

#### Operations

Bloom Filters support merging, as long as they are the same length. You
can OR all their items. If you must recalculate the length, that
requires recalculating all the items, which is likely not feasible.

Bloom filters support the union operation, which is done by bitwise XOR,
but the result will most likely have lots of collisions.

Deletion is not supported for Bloom Filters, since deleting the hash
could delete other items.

## Counting Bloom Filter

To allow for counting occurrences in a bloom filter, we can add another
array of counters corresponding to each bit in the filter\'s array.

Adding an item is similar to a bloom filter, except we first increment
the associated counter. If it changes from zero to one, we set the bit
in the filter.

The test operation is the same as well, since we just check the bloom
filter if necessary.

Now when we delete an element, we decrease the corresponding counter. If
the counter changes its value from one to zero, the corresponding bit in
the bit-array is unset.

### Properties

This allows us to delete items, but in exchange for more memory. How
much more memory? Well, the array must have a size of M, just like the
bit array. But since we\'re counting occurrences, we must at least be
able to count a few occurrences (in case of collisions). If 4 bits
sounds good (count up to 16) then we require 4x the memory of a bloom
filter.

We can use smaller (2-bit) bloom filters that can count up to 4 by
introducing a secondary hash table to manage overflowing counters (since
we assume this will be rarer).

We can also freeze an integer on insertion to the bloom filter (which
makes it only support probabilistic deletions).

## Quotient Filter

The quotient filter supports similar operations to a bloom filter, but
it has more data locality, supports deletions and can be dynamically
resized or merged.

The quotient filter uses a quotienting technique, which takes a number
`f` and returns its quotient `fq` and remainder `fr`. The hash function
should be uniform and independently distributed.

The quotientfilter data structure is represented by a compact open
addressing hash table, and uses linear probing to resolve insertions.
There are three metadata bits, all unset at the beginning:
`is_occupied`, `is_continuation`, `is_shifted`.

Otherwise, addition, deletion, merging are somewhat similar to hash
tables, and only take 15% more memory than a bloom filter.

## Cuckoo filter

Cuckoo filters use a multi-way associative Cuckoo hash table with m
buckets that can store b values. To insert a new element. The Cuckoo
filter algorithm uses Partial-Key Cuckoo hashing.

They have low space overhead, but are slower than normal bloom filters.

Prev: \[hashing](hashing.md) Next:
\[cardinality](cardinality.md)
