# Design Time Series Data

Let's say Time series data contains a pair of (timestamp, Val) where Val can be anything.

It generally helps if Val is also compressible, since timestamps will be compressible as well. Numbers work best -- free strings should be represented as enums if possible.

Take this graph of CPU usage

| **Unix timestamp** | **CPU usage (%)** |
| ------------------ | ----------------- |
| 1600000000         | 35.69             |
| 1600000015         | 34.44             |
| 1600000030         | 32.19             |
| 1600000044         | 53.94             |
| 1600000060         | 37.56             |

This would cost 8 bytes for the unix timestamp, and 8 bytes for an f64 for CPU usage.

## Optimization

To compress timestamps, the first thing to check is that they always increase. We can represent the Timestamps with delta encoding:

| **Unix timestamp** | **Delta** |
| ------------------ | --------- |
| 1600000000         | \-        |
| 1600000015         | 15        |
| 1600000030         | 15        |
| 1600000044         | 14        |
| 1600000060         | 16        |

We can record the first timestamp and then add deltas only (our deltas are representable in 14-16, so 2 bits will suffice.

| **Unix timestamp** | **Delta** | **Delta of deltas** |
| ------------------ | --------- | ------------------- |
| 1600000000         | \-        | \-                  |
| 1600000015         | 15        | \-                  |
| 1600000030         | 15        | 0                   |
| 1600000044         | 14        | \-1                 |
| 1600000060         | 16        | +2                  |

In GorillaDB's case, the delta of delta was 0 96% of the time, so this saved a lot of disk space.

## Optimizing Floating Point values

To optimize floating point values, we can successively XOR them, as long as they have high correlation (CPU usage goes from 0-100), so XORing them allows us to only calculate small differences and encode them -- since most of the values will end up as 0, the runs can be RLE'd away. This allows for f64s to be represented in 14 bits on average.

## Tagging vs. High Cardinality

Time series databases write a lot of data, so it's a cardinal sin to have data with high cardinality (many possibilities). For example, tagging errors with HTTP Codes isn't that bad, since there are only ~20 of them commonly used.

Thus, we'll maintain 20 time series in memory.

However, let's say we add accounts into the mix -- and we have 1M accounts. Well, now we have 20 * 1M or (20M) time series databases. This is quite expensive, and will either cost you lots of money or lots of compute.

## Aggregation vs. Raw Data

If we have data that is spread out in time, like so, and the timestamps have variable deltas and have an unpredictable distribution.

| **Timestamp** | **Cart size** |
| ------------- | ------------- |
| 1600000003    | 3             |
| 1600000007    | 14            |
| 1600000010    | 15            |
| 1600000011    | 9             |
| 1600000017    | 26            |
| 1600000017    | 5             |
| 1600000026    | 3             |

To handle this, we can use a histogram function, where we calculate some statistical occurrences from the above data (like min, max, p95, median, average, count) and then we throw away the original data.

This lets us save on space, but we lose the original data -- so we can't figure out what we got, just some basics. If we measure the wrong thing, we can't calculate the new thing again.
