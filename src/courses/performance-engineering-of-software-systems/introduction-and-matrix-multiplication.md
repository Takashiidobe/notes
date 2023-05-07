---
title: "Introduction and Matrix Multiplication"
---

# Introduction and Matrix Multiplication

Next: [bentley-rules-for-optimizing-work](bentley-rules-for-optimizing-work.md)

## Why do Performance Engineering?

At first, computers were very slow (on the order of KHz and a few MHz), so programs had to be ruthlessly optimized and simple to run.

Eventually though, computers hit the multi GHz level, and now even phones run at many Ghz.

Eventually, around 2005, Moore's law stopped for single core performance, and computers weren't getting any faster -- so computer manufacturers added more cores to their computers instead.

Nowadays, computers are big and complicated, with many layers of cache, SIMD registers, GPUs, FPGA's, etc.

As well, performance engineering jobs popularity as started to increase at this time.

## Matrix Multiplication Case Study

Let's optimize a matrix multiplication routine on an AWS Haswell Machine, which has about 836GFLOPS.

First in python, this takes ~6 hours.

```py
import sys, random
from time import *

n = 4096
A = [[random.random() for row in range(n)] for col in range(n)]
B = [[random.random() for row in range(n)] for col in range(n)]
C = [[0 for row in range(n)] for col in range(n)]

start = time()
for i in range(n):
    for j in range(n):
        for k in range(n):
            C[i][j] += A[i][k] * B[k][j]
end = time()
print("{%0.6f:end - start}")
```

This code does $2^37$ floating point operations, with a runtime of about 21042 seconds.

Python gets $2^37 / 21042 \approx 6.25 MFLOPS$. The peak is $\approx 836 GFLOPS$. Python is $\approx 0.00075%$ of the computer's usage.

You can rewrite the exact same program in Java, and get a runtime of 45 minutes, which is about 8.8x faster.

Or rewrite it in C and get a 2x extra speedup, so about 19 minutes.

Python is slow because it's interpreted, but it can be jitted to make it faster.

## Swapping Loop Order

Note that we can optimize this by changing the loop order of the program:

From this:

```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; i++) {
        for (int k = 0; k < n; i++) {
            C[i][j] += A[i][k] * B[k][k];
        }
    }
}
```

To this:

```c
for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; i++) {
        for (int j = 0; j < n; i++) {
            C[i][j] += A[i][k] * B[k][k];
        }
    }
}
```

This actually makes the program 20x faster. But why? Caching.

The processor wants to access memory in a cache efficient way, to decrease the amount of memory stalls a program has.

In this code, matricies are laid out in memory in row-major order.

Thus, since we rearranged the iteration order, the code becomes more cache efficient, and runs much faster.

We can use cachegrind to see the last-level-cache miss rate, which should help for this:

```sh
valgrind --tool=cachegrind ./program
```

| Loop order (outer to inner) | Running time (s) | Last-level-cache miss rate |
|-----------------------------|------------------|----------------------------|
| i, j, k                     | 1155.77          | 7.7%                       |
| i, k, j                     | 177.68           | 1.0%                       |

Just by swapping the iteration order, there are 7x fewer cache misses.

Optimization flags will also improve the performance of the matrix multiplication, so use `-O2`.

## Use Parallel Loops

You can also iterate through loops in parallel:

Take this:

```c
for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; i++) {
        for (int j = 0; j < n; i++) {
            C[i][j] += A[i][k] * B[k][k];
        }
    }
}
```

And replace it with this, which improves performance to 3s, since we can get an 18x parallel speedup.

```c
clik_for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; i++) {
        for (int j = 0; j < n; i++) {
            C[i][j] += A[i][k] * B[k][k];
        }
    }
}
```

## Tiling

We can use cache memory better by tiling, where we'd grab squares of A, B, instead of 1 by 1, and then use that to calculate and fill the square of C.

Doing this creates a 2x extra speedup.

## Recursive Matrix Multiplication

We can spawn background threads that will do the work, which improves performance again by about 20%.

## Use SIMD

With SIMD, we can also double the program's performance with `-march=native, -ffast-math`.

## Use Intrinsics

With intrinsics, we can also double the program's performance, and approach 352 GFLOPS, which is about 40% of the computer's peak performance.

This performance improvement is about 55000x what we started with.

Next: [bentley-rules-for-optimizing-work](bentley-rules-for-optimizing-work.md)
