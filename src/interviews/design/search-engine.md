# Design a Search Engine

## Problem

We'd like to design a search engine that allows our users to search all the text documents they provide and provide efficient and accurate search. We should allow for `AND` and `OR` queries, and have an algorithm that boosts results, since plain matching won't work well enough for us.

## Scale

- 25B documents
- search should complete in 2 seconds 99% of the time (SLA).
- Biggest customer has about 1B documents of ~1MB size.
- About 100k rps.

## Solution

## Data Structures

### Inverted Index

An inverted index contains the terms as well as the documents with which they match. The postings list is represented as a skip list, and terms are a linked list. The skip list can use pointer compression + XOR lists for smaller pointers.

| Terms   | Frequency | Postings           |
|---------|-----------|--------------------|
| elastic | 4         | [2, 9, 10, 49]     |
| index   | 2         | [1, 5]             |
| lucene  | 5         | [2, 5, 49, 50, 52] |
| shard   | 3         | [2, 9, 10]         |

To calculate conjuctions, we match the terms (elastic AND shard) both have matches in `[2, 9, 10]`. To show this on a bigger example, assume we have 3 matching documents:

2, 13, 17, 20, 98
1, 13, 22, 35, 98, 99
1,  3, 13, 20, 25, 80, 98

Take the shortest list and go to its first element (2). Create pointers as well at the other lists (1) and (1). We advance those two pointers, and we get (13) and (3). We know that 2 is not in this document.

Move onto 13. The second pointer is at 13, and the third pointer is less than 13, so we keep advancing till we hit >= 13. In this case, the third pointer finds 13, so we add it to our set.

We then continue on, and find 98 is also in every set as well.

For documents that are ORs, we calculate the union of the sets the same way.

## Regexes + Fuzzy Search

Regexes and fuzzy search can be represented as DFAs, which can be used to iterate through the term dictionary to find a match. Some backtracking DFAs have to be banned, but that's because they allow for exponential backtracking.

## Compression of Numeric Fields

Use Delta Encoding + Bit Packing: To encode, calculate the minimum and maximum value:
Min = 2
Max = 9
Max - min = 7
Deltas require 3 bits per value, and count 0 as the minimum value.
Encode deltas with 3 bits per value: ([3, 0, 0, 3, 7, 2]). This requires 18 bits instead of 48 bits, if you used a u8.

| Doc ID | Price |
|--------|-------|
| 0      | 5     |
| 1      | 2     |
| 2      | 2     |
| 3      | 5     |
| 4      | 9     |
| 5      | 4     |

If there are less than 256 unique values, you can sort them and count occurrences with counting sort.

## Timestamps

To compress timestamps, we can use GCD compression:

Calculate the minimum value (1), calculate the deltas:
[10, 30, 20, 0, 70, 50], compute the GCD, encode the minimum value and the GCD, and then encode quotients with bit packing:

[1, 3, 2, 0, 7, 5]

| Doc ID | Price |
|--------|-------|
| 0      | 11    |
| 1      | 31    |
| 2      | 21    |
| 3      | 1     |
| 4      | 71    |
| 5      | 51    |

## Sorted Sets vs Bitmaps

- Sorted Sets are useful for sparse data but sorted, but bad for dense data (that's where bitmaps come in). We can optimize bitmaps by using compression (Run length encoding) or using something like roaring, which is a hybrid. There's also work to create learned indexes (in the paper, they beat B-Tree indexes by 70% by replacing them with neural nets that look at access patterns and create a better index).

## Cardinality

How do you find the length of a set? With Hyperloglog++, you calculate the longest run of 0s or 1s in every item, and then you use that to approximate how many occurrences there are.

But imagine you get unlucky: you count 50 items, but one of them has a run of 10 0s (so you'd approximate 1024 items).

We can do better, though, with Stochastic Averaging:

Use 4 registers, and find a way to hash each item into the 4 registers.

Assume we got [1024, 4, 8, 2] for our numbers. We then calculate the harmonic mean times number of registers:

4 * 4 / (1 / 1024 + 1 / 4 + 1 / 8 + 1 / 2) ~= 18.3

This allows for less weight to outliers.

This also allows for loseless unions (just take the max, or min, or whatever of each number).
