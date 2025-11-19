---
title: "Ddsketch A Fast And Fully Mergeable Quantile Sketch With Relative Error Guarantees"
pdf_url: "[[ddsketch-a-fast-and-fully-mergeable-quantile-sketch-with-relative-error-guarantees.pdf]]"
---
## Notes

DDSketch is a relative error quantile sketch designed for heavy-tailed data streams.

It has 3 guarantees:

1. The estimate, $\tilde{x}_q$ for any quantile $q$ satisfies $|\tilde{x}_q - x_q| \le \alpha$, so the difference is configurable to $\alpha$.
2. Merging sketches is as accurate as sketching the union.
3. Insert and merge are fast.

## Setting up buckets

So, for a value of  $\alpha$, which is chosen relative error, define $\gamma$ as:
$$
\gamma = \dfrac{1 - \alpha}{1 + \alpha}.
$$
The positive real line is partitioned into buckets:
$$B_i : \gamma^{i-1} < x \le \gamma^i,\ i \in \mathbb{Z}.$$
Each bucket $B_i$ stores a count of how many observations fell into the range.
Given a value $x > 0$, its bucket index is $i = \left\lceil \log_{\gamma} x \right\rceil.$

## To answer a query

Approximate the $q$, where there are $n$ observations by:

- Computing a rank target, $r = q(n - 1)$.
- Scan buckets by increasing $i$, accumulating counts until $\sum_{i = 0}^{n} \gt r$ . Take that $i$, and return the bucket's representative. $\tilde{x}_q = \dfrac{2 \gamma^i}{\gamma + 1}$.
## Limiting Memory

Since naively the number of non-empty buckets grows linearly to $n$, to keep memory bounded by $m$, DDSketch limits the maximum number of buckets to $m$.

- Then, when there are too many non-empty buckets, it collapses the two lowest index buckets.
- Say the two lowest index buckets are $B_0$ and $B_1$. Then, do a merge, where $B_0$'s items are moved to $B_1$.
- Accuracy is sacrificed for lower values, not the tails, unless the memory requirement, $m$, is extremely low.

## Theoretical Bounds

As long as the distribution is heavy tailed, like a lognormal distribution, then the memory usage only grows logarithmically.
If $\alpha = 0.01$, a sketch with a thousand buckets can maintain high quality high-quantile estimates with 1% relative error for millions of samples.

## Example in Python

An example like this will accurately guess with only a thousand buckets.

```sh
Approx p50 = 0.9900000000000001
Approx p90 = 3.632761126626586
Approx p99 = 10.074696689511331
```

```python
import math
from collections import defaultdict


class DDSketch:
    """
    Minimal DDSketch implementation for non-negative values.

    - Relative error: alpha (0 < alpha < 1)
    - Bucket boundaries: (gamma^(i-1), gamma^i], i in Z
    - max_buckets: if not None, collapse lowest buckets to enforce a size limit
    """

    def __init__(self, alpha=0.01, max_buckets=1000):
        if not (0 < alpha < 1):
            raise ValueError("alpha must be in (0, 1)")
        self.alpha = alpha
        self.gamma = (1 + alpha) / (1 - alpha)
        self.log_gamma = math.log(self.gamma)

        self.max_buckets = max_buckets

        # index -> count
        self.buckets = defaultdict(int)
        self.zero_count = 0  # for x == 0
        self.count = 0

        self.min_value = None
        self.max_value = None

    def _bucket_index(self, x: float) -> int:
        """Map x > 0 to bucket index i = ceil(log_gamma(x))."""
        return math.ceil(math.log(x) / self.log_gamma)

    def add(self, x: float):
        """Insert a single observation x >= 0."""
        if x < 0:
            raise ValueError("This simple implementation supports only non-negative values")

        if self.count == 0:
            self.min_value = x
            self.max_value = x
        else:
            self.min_value = min(self.min_value, x)
            self.max_value = max(self.max_value, x)

        self.count += 1

        if x == 0.0:
            self.zero_count += 1
            return

        i = self._bucket_index(x)
        self.buckets[i] += 1

        if self.max_buckets is not None and len(self.buckets) > self.max_buckets:
            self._collapse_lowest_bucket()

    def _collapse_lowest_bucket(self):
        """
        Collapse the lowest-index bucket into the next one, as in the paper.
        This preserves relative accuracy for higher quantiles.
        """
        if not self.buckets:
            return

        # Smallest index with data
        i0 = min(self.buckets.keys())

        # Next index with data (if any)
        higher_indices = [i for i in self.buckets.keys() if i > i0]
        if not higher_indices:
            # Only one bucket; nothing meaningful to collapse into.
            return

        i1 = min(higher_indices)

        self.buckets[i1] += self.buckets[i0]
        del self.buckets[i0]

    def merge(self, other: "DDSketch"):
        """
        Merge another DDSketch into this one. Both must share the same alpha/max_buckets.
        """
        if not isinstance(other, DDSketch):
            raise TypeError("Can only merge another DDSketch")

        if other.alpha != self.alpha or other.gamma != self.gamma:
            raise ValueError("Cannot merge sketches with different alpha/gamma parameters")

        self.count += other.count
        self.zero_count += other.zero_count

        if self.min_value is None:
            self.min_value = other.min_value
            self.max_value = other.max_value
        elif other.min_value is not None:
            self.min_value = min(self.min_value, other.min_value)
            self.max_value = max(self.max_value, other.max_value)

        for i, c in other.buckets.items():
            self.buckets[i] += c

        # Enforce bucket limit
        if self.max_buckets is not None:
            while len(self.buckets) > self.max_buckets:
                self._collapse_lowest_bucket()

    def _bucket_value(self, i: int) -> float:
        """
        Representative value for bucket i.
        The paper uses 2 * gamma^i / (gamma + 1).
        """
        return 2.0 * (self.gamma ** i) / (self.gamma + 1.0)

    def quantile(self, q: float) -> float:
        """
        Return an approximate q-quantile for 0 <= q <= 1.

        For q=0 and q=1, this effectively returns something near min/max.
        """
        if not (0.0 <= q <= 1.0):
            raise ValueError("q must be in [0, 1]")
        if self.count == 0:
            raise ValueError("Cannot query an empty sketch")

        # Rank target in [0, n-1]
        target_rank = q * (self.count - 1)

        # Handle zeros first
        if target_rank < self.zero_count:
            return 0.0

        remaining_rank = target_rank - self.zero_count

        # Iterate buckets in ascending order of index
        cumulative = 0
        for i in sorted(self.buckets.keys()):
            c = self.buckets[i]
            if c == 0:
                continue
            if cumulative + c > remaining_rank:
                return self._bucket_value(i)
            cumulative += c

        # If we get here, numerical/rounding edge case; return max bucket value
        max_i = max(self.buckets.keys())
        return self._bucket_value(max_i)


if __name__ == "__main__":
    import random

    sketch = DDSketch(alpha=0.01, max_buckets=1000)

    # Simulate some positive, skewed data (e.g., log-normal latencies)
    for _ in range(10_000):
        x = math.exp(random.gauss(0, 1.0))  # lognormal-ish
        sketch.add(x)

    for q in [0.5, 0.9, 0.99]:
        print(f"Approx p{int(q*100)} =", sketch.quantile(q))
```

