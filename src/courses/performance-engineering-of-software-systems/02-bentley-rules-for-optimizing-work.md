---
title: "Bentley Rules for Optimizing Work"
pdf: "[[02-bentley-rules-for-optimizing-work.pdf]]"
---

# Bentley Rules for Optimizing Work

Prev: [[01-introduction-and-matrix-multiplication]]
Next: [[03-bit-hacks]]

## Reducing Work

Reducing the work of an algorithm might seem to make it faster, but with the complex nature of computers, with instruction-level parallelism, caching, vectorization, speculation and branching, etc, it might not always be faster.

It's a good first step, however.

This lecture talks about the "New Bentley" Rules for performance, which fall into four categories:

1. Data Structures
2. Loops
3. Logic
4. Functions

## Data Structures

### Packing and Encoding

We could pack and encode data in fewer bits. Take "September 11, 2018", which can be stored as a datetime in 18 bytes. However, we could pack this data into a smaller struct.

Split off each part of the date into a minimal representation:

```c
struct {
    int year: 13;
    int month: 4;
    int day: 5;
} date_t;
```

This only takes 22 bits instead of 128 bits.

### Augmentation

Data structure augmentation involves adding information to a data structure to make common operations do less work.

For example, appending to a linked list is an $O(n)$ operation, since we need to start at the head, walk to the end, and then add the new node.

If this is a common operation, we could add a tail pointer that always points to the last node in the list, to make appending $O(1)$.

### Precomputation

If you need to calculate something precomputable (i.e. at compile time), you can reduce everything to a lookup table at compile time.

### Compile-Time Initialization

For example, C++ and Rust have `constexpr` and `const` to force the compiler to calculate a value at compile time and include it into the binary. Thus, if a value is computable at compile time, itcan be transformed into a fast data lookup.

### Caching

Caching stores results that have been accessed recently so the program doesn't need to compute them again.

In python, `@cache` is a decorator that will do this for you.

### Sparsity

Sparsity involves avoiding storing and computing common values.

Imagine you have a matrix of millions of values, but only a few of them are actually set. Instead of wasting all the space holding zeroes, create a map of (row, col) -> val, and iterate through that instead. You can also use a faster data structure, like a roaring bitmap.

For graphs, you can also store a sparse graph this way, where if they store the same value, you can point to a value in the array, compressing it.

## Logic

### Constant Folding and Propagation

Constant folding is the idea of evaluating constant expressions and substituting the result into further expressions, all at compile time.

```c++
constexpr double radius = 6371000.0;
constexpr double diameter = 2 * radius; // all done at compile time.
```

### Common Subexpression Elimination

Common Subexpression Elimination means to avoid computing the same expression multiple times, instead just storing it in a variable for later use.

### Algebraic Identities

Exploit algebraic identities by replacing expensive algebraic expressions with simpler ones that do the same work. This can be done with approximations -- you can approximate many things with a substitution that is computationally less expensive. One example is to use a taylor series to approximate a value in [0, 1].

### Short-Circuiting

When performing a series of tests, stop evaluating as soon as you know the answer.

Guard clauses are a good example of this: if you know something's wrong and you can't keep computing, check for that first.

### Ordering Tests

Tests should be ordered to perform those that are more successful before tests that are rarely successful. As well, inexpensive tests should precede expensive ones.

Instead of:

```c
bool is_whitespace(char c) {
    return c == '\r' || c == '\t' || c == ' ' || c == '\n'; // slow, because carriage returns are rare
}
```

```c
bool is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r'; // slow, because spaces and newlines are common
}
```

### Creating a Fast Path

Creating a fast path involves having a way to bail out of more expensive computation if some conditions are met.

Say if you're trying to find out if two circles are colliding, you could check if their squares are touching. If they aren't, then there's no way that they're colliding, and computing collisions of squares is cheaper than circles.

### Combining Tests

The idea of combining tests is to replace a sequence of tests with one test or switch. Your compiler may be able to turn this into just one jump.

## Loops

### Hoisting

The goal of hoisting code is to avoid recomputation of loop invariant code each time through the body of a loop.

```c
void scale(double *X, double *Y, int N) {
    for (int i = 0; i < N; i++) {
        Y[i] = X[i] * exp(sqrt(M_PI/2)); // expensive, always calculating factor.
    }
}
```

```c
void scale(double *X, double *Y, int N) {
    const double factor = exp(sqrt(M_PI/2)); // hoist outside of the loop to only calculate once.
    for (int i = 0; i < N; i++) {
        Y[i] = X[i] * factor;
    }
}
```

### Sentinels

Sentinels are special dummy values placed in a data structure to simplify the logic of boundary conditions.

You can use some constant for this, like $\infty$.

### Loop Unrolling

Unrolling a loop may give better performance, but your compiler is probably good enough at this these days.

### Loop Fusion

You can save the overhead of looping twice by fusing two loops over the same index range into a single body:

```c
for (int i = 0; i < n; i++) {
    C[i] = (A[i] <= B[i]) ? A[i] : B[i];
}
for (int i = 0; i < n; i++) {
    D[i] = (A[i] <= B[i]) ? B[i] : A[i];
}
```

```c
for (int i = 0; i < n; i++) {
    C[i] = (A[i] <= B[i]) ? A[i] : B[i];
    D[i] = (A[i] <= B[i]) ? B[i] : A[i];
}
```

### Eliminating Wasted Iterations

You should modify loop bounds to avoid executing loop iterations over empty loop bodies:

```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (i > j) { /* do something */ }
    }
}
```

```c
for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
        /* do something */
    }
}
```

## Functions

### Inlining

Inlining avoids function overhead call by replacing a call to the function with the body of the function:

The compiler does this better most of the time, but you can say: `#[inline]` in rust as a suggestion.

### Tail-Recursion Elimination

Replace a recursive call that occurs as the last step of a function with a branch, saving function-call overhead:

```c
void quicksort(int *A, int n) {
    if (n > 1) {
        int r = partition(A, n);
        quicksort(A, r);
        A += r + 1;
        n -= r + 1;
    }
}
```

### Coarsening Recursion

Increase the size of the base case and handle it with more efficient code to avoid function-call overhead.

Prev: [[01-introduction-and-matrix-multiplication]]
Next: [[03-bit-hacks]]
