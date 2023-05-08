# Hyperloglog

We want to count how many distinct filenames were created in the past 24
hours, but the collection is too big to fit in memory, or a single
server.

In exchange, hyperloglog is approximate.

The probability that a random string of bits has K leading zeroes is 1 /
2 ^ K.

1. Counting leading zeroes works on random numbers, not arbitrary input.
  - Solution: hash input
2. The distribution of leading zeroes is affected by duplication
  - Solution: just consider the maximum leading zeroes.
3. Estimation can have huge error.
  - Run the algorithm multiple times with multiple sources of randomness
    (more than one hash function), and calculate more than once, and
    sample the data (grab a random chunk of it).

The algorithm divides the stream of elements into `m` independent buckets
and calculates the HLL by calculating the harmonic mean of the buckets.

Hyperloglog improves this by throwing out the top 30% of the buckets
with the highest values, as this decreases error from 1.3/sqrt(m) to
1.05/sqrt(m). Also, the harmonic mean decreases this error to
1.04/sqrt(m).
