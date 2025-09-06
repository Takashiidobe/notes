---
title: Hashing and Randomized Algorithms
date created: Friday, November 17th 2023, 9:31:11 am
date modified: Thursday, July 24th 2025, 10:18:08 pm
---

# Hashing and Randomized Algorithms

Prev: [divide-and-conquer](divide-and-conquer.md)
Next: [graph-traversal](graph-traversal.md)

## Exercises

### Probability

6-1. You are given `n` unbiased coins, and perform the following process to generate
all heads. Toss all n coins independently at random onto a table. Each round
consists of picking up all the tails-up coins and tossing them onto the table
again. You repeat until all coins are heads.
(a) What is the expected number of rounds performed by the process?

$(log n) + 1$. Assume we start out with 8 coins. On the first round, 4 should be heads and 4 should be tails. Then we flip and get two more heads, so two coins remain. And it should take two rounds to flip both to heads.

(b) What is the expected number of coin tosses performed by the process?

We would expect to flip $\frac{n}{2}$ of the coins once, then $\frac{n}{4}$ of the coins twice, etc. This could be shown as:

$$(\frac{n}{2} * 1) + (\frac{n}{4} * 2) \dots + (\frac{n}{n} * n)$$

$\frac{n}{2}$ coin tosses per round, with $(log n)$ rounds, so on the order of $\frac{n}{2} log n$

6-2. Suppose we flip `n` coins each of known bias, such that $p_i$ is the probability of
the `ith` coin being a head. Present an efficient algorithm to determine the exact
probability of getting exactly `k` heads given $p_1,\dots, p_n \in [0, 1]$.

The simplest algorithm is to sum up the probabilities of heads and then dividing it by `len(n)`. This would give us the probability of all the heads in the sequence averaged out.

6-3. An inversion of a permutation is a pair of elements that are out of order.
(a) Show that a permutation of n items has at most n(n − 1)/2 inversions.
Which permutation(s) have exactly n(n − 1)/2 inversions?
(b) Let P be a permutation and P r be the reversal of this permutation. Show
that P and P r have a total of exactly n(n − 1)/2 inversions.
(c) Use the previous result to argue that the expected number of inversions in
a random permutation is n(n − 1)/4.

6-4. A derangement is a permutation p of ${1,\dots, n}$ such that no item is in its
proper position, that is, $pi \ne = i$ for all $1 \le i \le n$. What is the probability that a
random permutation is a derangement?

### Hashing

6-5. An all-Beatles radio station plays nothing but recordings by the Beatles,
selecting the next song at random (uniformly with replacement). They get
through about ten songs per hour. I listened for 90 minutes before hearing a
repeated song. Estimate how many songs the Beatles recorded.

90 minutes at 10 songs per hour is 15 songs. Since a collision in set $n$ happens if there are $n^2$ items, I would guess around 225 songs.

6-6. Given strings `S` and `T` of length n and m respectively, find the shortest
window in `S` that contains all the characters in `T` in expected $O(n + m)$ time.

First, I would create a hashmap of character -> count of `S` and `T`. I would then allocate two pointers, a start pointer and an end pointer.
I would try to increment the start pointer and decrement the end pointer. When doing so, I would try to remove the current character from `S`, and then compare its value to `T`. If `S` no longer has enough of a character, I would stop incrementing it, and the same for the end pointer, just with decrement.

6-7. Design and implement an efficient data structure to maintain a least recently
used (LRU) cache of n integer elements. A LRU cache will discard the least
recently accessed element once the cache has reached its capacity, supporting
the following operations:

- get(k)– Return the value associated with the key k if it currently exists in
the cache, otherwise return -1.

- put(k,v) – Set the value associated with key k to v, or insert if k is not
already present. If there are already n items in the queue, delete the least
recently used item before inserting (k, v).
Both operations should be done in O(1) expected time.

Create a hashmap and a doubly linked list, where the hashmap points to the node in the doubly linked list. The doubly linked list allows for $O(1)$ relocations, and the hashmap allows for get, update, and delete in $O(1)$.

### Randomized Algorithms

6-8. A pair of English words (w1, w2) is called a rotodrome if one can be circularly
shifted (rotated) to create the other word. For example, the words (windup,
upwind) are a rotodrome pair, because we can rotate “windup” two positions
to the right to get "upwind."
Give an efficient algorithm to find all rotodrome pairs among `n` words of length
`k`, with a worst-case analysis. Also give a faster expected-time algorithm based
on hashing.

I assume the "efficient" way is to sort the items and then bucket them that way, but this is $O(n log n * k)$.

To first lower the search time of finding a rotodome, create a hashmap of {chars: count} -> word.
This would create buckets where there would be words that could be possible rotodomes.
Within each bucket, we would mark pairs as being rotodomes by associating a left and a right of the pair.
We would then mark the indexes of the left as $0..n-1$, where $n$ is the length of left, and then see if right matches the bitonic (always increasing until the maximum then decreasing or vice-versa) of left. If so, the two are rotodomes.

This would still take $O(nk)$ time in worst case, but should be closer to $O(n)$ time in average case, since there shouldn't be that many matching pairs on a normal input.

6-9. Given an array w of positive integers, where w[i] describes the weight of
index i, propose an algorithm that randomly picks an index in proportion to its
weight.

One way to do this would be to sum the total of all the weights, and then for each item in the array, you would allocate another array that is its value divided by the sum total. That way, you can work out the percentage range that each item occupies. Then, you would turn this array into a prefix sum, and then call `randrange(0..sum)`. When you get a number, you could look up the valid range that corresponds to that number.

6-10. You are given a function rand7, which generates a uniform random integer
in the range 1 to 7. Use it to produce a function rand10, which generates a
uniform random integer in the range 1 to 10.

`rand7` has an entropy of $log_2 7$ and `rand10` has an entropy of $log_2 10$. Thus, we require at least $\frac{log_2 10}{log_2 7}$ calls to `rand7` to generate enough entropy for a `rand10` call, which is ~1.2.

To solve any `randm` to `randn` we can multiply the result of `randm` by `randm` as many times as required until the result > `n`. Finally, we would find the greatest divisor of both this new number and `n`. Then we modulo off, and reroll if we don't fit into this area.

```python
rand10_from_rand7():
    rand40 = float('inf')
    while rand40 >= 40:
        rand40 = (rand7() - 1) * 7 + rand7() - 1
    return rand40 % 10 + 1
```

If we had to generate more than one number at a time, then rolling `rand7` to generate a larger number and then moduloing off certain areas of that number would work.

6-11. Let $0 \lt α \lt 1/2$ be some constant, independent of the input array length
n. What is the probability that, with a randomly chosen pivot element, the
partition subroutine from quicksort produces a split in which the size of both
the resulting subproblems is at least α times the size of the original array?

The probability is $$ Pr = \frac{1}{n}(n - 2n\alpha) = 1 - 2\alpha $$.

6-12. Show that for any given load $m/n$, the error probability of a Bloom filter is
minimized when the number of hash functions is $k = exp(−1)/(m/n)$.

We minimize $$ f(k) = \left(1 - \left(1 - \frac{1}{m}\right)^{kn}\right)^k $$ which results in $k = \frac{m}{n} \log 2$

Prev: [divide-and-conquer](divide-and-conquer.md)
Next: [graph-traversal](graph-traversal.md)
