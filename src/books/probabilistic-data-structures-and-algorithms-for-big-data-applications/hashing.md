---
title: hashing
---

# Hashing

Next: [membership](membership.md)

`Hashing` is crucial to probabilistic data structures. They `randomize`
and `compact` representation of data.

A `hash function` compresses blocks of input data by generating an
identifier of a smaller size, called the `hash`.

Note: Hash functions compress input, therefore, cases where they
generate the same hash values for two different blocks of data are
unavoidable. These are called `hash collisions`.

For universal hashing, one simple hash function looks like this:

    h{k}(x) = (k * x mod p) mod m;

`k` is a randomly chosen integer where `k != 0`. `k` is moduloed with
`p`, a randomly selected prime number which must be `>=` `m` (normally a
Mersenne prime number, like `2^31 - 1` for `p` and an `m` which is
roughly the same order of magnitude (`2^31 - 1` `~=` `2*10^9` so it
works well here)).

This is an approximate algorithm which provides a probability of
collision smaller than `2/m`.

This hash function only works for inputs on integers. This doesn't work
well for applications that need to hash variable-sized vectors with
certain guaranteed properties.

## Cryptographic hash functions

`cryptographic hash functions` are fixed mappings from variable input
bit strings to fixed length output bit strings.

Hash collisions are unavoidable, but a desirable property of a
`secure hash function` is to be `collision resistant`, which means that
it should be hard to find collisions.

There are three requirements for cryptographic hashes, since they arre
used to verify authenticity.

1.  `Work factor` - to make brute force inversion hard, a cryptographic
    hash should be computationally expensive.
2.  `Sticky state` - cryptographic hashes should not have a state in
    which it can stick for a plausible input pattern.
3.  `Diffusion` - every output bit of a crytographic hash should be an
    equally complex function of every input bit.

Cryptographic functions can be further divided into:

1.  `keyed hash functions` (which use a secret key)
2.  `unkeyed hash functions` (which have no keys)

Probabilistic data structures use only unkeyed hash functions like:

1.  `One-Way hash functions`
2.  `Collision Resistant hash functions`
3.  `Universal One-Way hash functions`

`One-Way hash functions` have these properties:

1.  They can be applied to blocks of data of any length.
2.  They produce a fixed-length output.
3.  They have `preimage resistance` (`one-way property`), which makes
    them hard to invert. It should be computationally infeasible to find
    an input that maps to a hashed output.

`Collision Resistant hash functions` should have this property:

1.  It should be extremely unlikely for two different inputs to generate
    the same hash value.

`Universal One-Way hash functions` should have this property:

1.  It should be `target collision resistant`, or
    `second-preimage collision resistant` - it should be computationally
    infeasible to find a second distinct input that hashes to the same
    output as the specified input.

Note: Cryptographic hash functions are much slower than
non-cryptogrpaphic ones. `SHA-1` can hash `540 MiB/second`, but
non-cryptographic functions are `2500 MiB/second` or more.

### Message-Digest Algorithms

`MD5` was invented by Ron Rivest in 1991 to replace `MD4`. It takes a
message of arbitrary length and produces an output the unique 128-bit
hash of the input.

`MD5` is based on the `Merkle-Damgard` schema. It converts the input of
an arbitrary size to a number of blocks of fixed size (512-bit blocks or
16 32-bit words). Each block is processed one by one using a special
compression function and every next block uses the result of the
previous output. To make the compression secure, the algorithm applies
`Merkle-Damgard` strengthening, then the padding uses the encoded length
of the original message. The final `MD5` hash is the 128-bit value
generated after processing the last block.

`MD5` is now considered vulnerable to collision attacks. Attackers can
construct different messages with the same `MD5` hash, so downloaders
cannot verify the authenticity of the file.

### Secure Hash Algorithms

### SHA

`Secure Hash Algorithms` (SHA) were developed by the NSA and published
by the NIST. The first algorithm, `SHA-0` was published in 19931, and
was replaced by `SHA-1`. `SHA-1` produces a longer 160-bit value.

`SHA-1` was widely used, until in 2005 a weakness in `SHA-1` was
discovered and in 2010 it was deprecated for use as a
`cryptographically secure` hash algorithm.

`SHA-2` was published in 2001 and includes various digest sizes:
`SHA-224`, `SHA-256`, `SHA-384`, `SHA-512`.

### RadioGatún

RadioGatún is an improvement of the Panama hash function. The algorithm
splits the input into a sequence of blocks which are injected into the
algorithm's internal state using a special function. That is followed
by an iterative application of single non-cryptographic functions (the
belt-and-mill).

Note: RadioGatún is claimed to be much faster than `SHA-256` while still
being cryptographically secure.

## Non Crytographic hash functions

### Fowler/Noll/Vo

FNV is a non-cryptographic hash that maintains an internal state is
initialized to a special offset basis. Then, it iterates over 8 bits at
a time and performs multiplication of the state on some large numerical
constant (FNV Prime) by applying XORs to the input block. After the last
input, the resulting value is reported as the hash.

Most of this has to do with the selection of the prime number.

There is an alternate algorithm, which switches the order of the
multiplication and the XOR over the range.

The FNV algorithm has (32, 64, 128, 256, 512, and 1024 bit hash values).

It is used in Rust's hashmaps as a crate.

### MurmurHash

Published in 2008 by Appleby. It consists of a Multiply (MU) and Rotate
(R) in that order. Murmurhash takes a key, a length, and a seed.

It iterates through the list in chunks of 4, and then does a rotation
through the input, using the seed to finalize the output hash.

Murmurhash is used in libstdc++, Elasticsearch, Cassandra, Hadoop,
nginx.

### CityHash

Published in 2011 at Google by Pike and Alakuijala. CityHash is made for
use on short strings, and performs well on such inputs, but is slower
and more complex than MurmurHash for most other inputs.

## Hash Tables

A hash table is a dictionary data structure that is comprised of an
unordered associate array of length m, whose entries are called buckets
and are indexed by a key in the range of {0, 1, ..., m - 1}.

A hash function is used to compute the key that is utilized to select
the appropriate bucket to store the value.

Since the size of the universe (all possible inputs) is larger than our
hash table, there will be collisions that need to be dealt with.

The load factor `α` can be represented by the ratio of the used keys `n`
to a table's total length `m`.

$$α = frac{n}{m}$$

To deal with collisions, there are two main strategies:

- Closed addressing - store collided elements under the same keys in a
  second data structure.
- Open addressing - store collided elements in positions other than
  their preferred positions and find a way to address them.

`separate chaining` stores items that collide in a linked list.
`perfect hashing` uses special hash functions and secondary hash tables
of different lengths.

Let's talk about some open addressing implementations:

### Linear Probing

Create a hash table as a circular array (ring buffer).

To insert a new element x, we compute its key $$k = h(x)$$ using a
hash function `h`. If the bucket is filled, we keep going clockwise
until we find a free space to drop the item.

We must have a load factor < 1, otherwise the hash table will run out
of elements.

To calculate lookup, we compute the key `k` using the hash function `h`
and start checking the buckets clockwise. If we find the wanted element
x, then we know it's in the table. If we find an empty bucket, the
element is not in the table.

The algorithm requires O(1) time on average for each operation, as long
as the linear probing hash table is not full.

The longest probe sequence is expected of length O(log n).

### Cuckoo Hashing

Cuckoo hashing uses two hash functions instead of one.

It hashes the item twice, and gets two keys.

If neither bucket is occupied, randomly place the item into a bucket.

If one bucket is occupied, place the item in the other.

If both buckets are occupied, then place one of the candidate buckets,
and put the element into it. The item that was evicted then goes to its
other candidate bucket. If that one is filled, then the evicted item
goes into that bucket, and the evicted item changes.

## Conclusion

Next Chapter is on probabilistic data structures and extensions of hash
tables, called filters.

Next: [membership](membership.md)
