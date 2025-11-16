---
title: "Hashed sorting is typically faster than hash tables"
source: "https://reiner.org/hashed-sorting"
author:
  - "[[Reiner’s webpage and articles.]]"
published:
created: 2025-09-08
description: "Benchmarks and theoretical explanation of why and when hashed radix sort beats hash tables."
tags:
  - "clippings"
---
Problem statement: count the unique values in a large array of mostly-unique uint64s. Two standard approaches are:

- Insert into a hash table and return the number of entries.
- Sort the array, then count positions that differ from their predecessor.

Hash tables win the interview ( $O(n)$ vs $O(n \log n)$ ), but sorting is typically faster in a well-tuned implementation. This problem and its variants are the inner loop of [some of the world’s biggest CPU workloads](https://reiner.org/#applications).

## Benchmark highlights

Here is performance on M2 Pro, comparing our best-tuned hash table and our best-tuned sorting implementation. We also include Rust’s default implementations (`sort_unstable()`, and `HashSet` with `foldhash::fast`) as a reference point for high-quality general-purpose implementations:

| Data size | Baseline hash table | Baseline sorting | Tuned hash table | Tuned sorting |
| --- | --- | --- | --- | --- |
| 8 KiB | 3.8 µs | 5.1 µs | **1.6 µs** | 6.5 µs |
| 256 KiB | 219 µs | 264 µs | 193 µs | **92 µs** |
| 8 MiB | 8.1 ms | 12.0 ms | 7.1 ms | **3.9 ms** |
| 256 MiB | 875 ms | 464 ms | 269 ms | **185 ms** |
| 2 GiB | 7.6 s | 4.3 s | 2.6 s | **1.9 s** |

Tuned sorting beats our best hash table by ~1.5× on non-tiny sizes, and is up to 4× faster than the excellent [“Swiss Table”](https://www.youtube.com/watch?v=ncHmEUmJZf4) hash tables that ship with Rust’s standard library.

[Benchmark code is available](https://github.com/reinerp/hashed-sorting-benchmark).

## Why does sorting win?

Memory bandwidth: *even though sorting makes multiple passes through memory, each pass uses bandwidth far more efficiently than a hash table’s single pass.*

Once the dataset outgrows CPU caches (often around ~1 MiB on a single core, CPU-dependent), both hashing and sorting become limited by cache-line fetch bandwidth to main memory. Cache lines are typically 64 bytes, and the CPU fetches the entire line if you touch even a single byte.

Hash tables waste bandwidth: each 8-byte key access pulls a full 64-byte cache line. So a hash table must incur at least 128 bytes of traffic per uint64 processed: 64 bytes read and 64 bytes written.

For sorting we use a radix sort that splits into 1024 buckets per pass, needing just 3 passes for $2^{30}$ elements. Each pass reads and writes the entire array once, and the accesses have enough spatial locality that the *whole* cache line is used productively, unlike in hash tables. So processing a single uint64 takes only 48 bytes of memory traffic: 8 bytes × 3 passes of reads, 8 bytes × 3 passes of writes.

This analysis would suggests a 2.7× speedup vs. hash tables: 128 bytes vs. 48 bytes of memory traffic per uint64. The measured speedup is only ~1.5×, primarily (as far as I can tell) because it’s harder to make the CPU cache system do exactly what you want for radix sort than for hash tables. Hash tables get closer to their ideal than radix sort; radix sort’s ideal is better enough that it still wins.

## Making radix sort robust

Although radix sort is often the fastest sorting algorithm on random data, its performance degrades on data that isn’t uniformly spread out over the key space. One pass sorts one byte of the key into 256 buckets; if only a small subset of the 256 buckets are used by keys in practice—for example, if the top byte of a uint64 is always zero—then a lot of the work on that pass of radix sort may be wasted.

To show this, I benchmarked sorting on (a) random uint64s and (b) uint64s where the random bits are “spread out”: even bits random, odd bits zero, like $0a0b0c0d\ldots$ . For the spread-out numbers, each radix pass uses only 16 of 256 buckets, hurting efficiency. Radix sort is ~2× faster than quicksort on random numbers, but ~1.5× slower on spread-out numbers:

| Data size | Quicksort | Radix sort |
| --- | --- | --- |
| 8 KiB (random) | 5.1 µs | **4.8 µs** |
| 256 KiB (random) | 262 µs | **111 µs** |
| 8 MiB (random) | 11.9 ms | **5.4 ms** |
| 256 MiB (random) | 466 ms | **267 ms** |
| 2 GiB (random) | 4.2 s | **2.8 s** |
| 8 KiB (spread-out) | **5.2 µs** | 6.3 µs |
| 256 KiB (spread-out) | **262 µs** | 459 µs |
| 8 MiB (spread-out) | **12.2 ms** | 17.4 ms |
| 256 MiB (spread-out) | **462 ms** | 628 ms |
| 2 GiB (spread-out) | 4.2 s | **3.2 s** |

To avoid these slowdowns, we borrow an idea from hash tables: sort by `hash(key)` rather than `key`. For counting uniques we don’t care about final order, only grouping. Of course, this will change the sort order, but given that we’re only interested in counting uniques rather than the sort order per se, this doesn’t matter.

Better yet, use an invertible ([bijective](https://en.wikipedia.org/wiki/Bijection)) hash to transform keys in place. That avoids storing both key *and* hash, or recomputing the hash each pass. Many widely used hash functions are invertible on `uint64`; I used [Murmur3](https://github.com/reinerp/hashed-sorting-benchmark/blob/174a64335e879ad367a5393892ebd8461529af58/src/hashers.rs#L19) and a cheaper variant, [MulSwapMul](https://github.com/reinerp/hashed-sorting-benchmark/blob/174a64335e879ad367a5393892ebd8461529af58/src/hashers.rs#L43).

With a reasonably fast hasher, the cost of hashing is cheap and it fixes bad distributions. Using MulSwapMul, performance looks like this mostly regardless of data distribution:

| Data size | Hashed radix sort |
| --- | --- |
| 8 KiB | 6.5 µs |
| 256 KiB | 92 µs |
| 8 MiB | 3.9 ms |
| 256 MiB | 185 ms |
| 2 GiB | 1.9 s |

This is the “best algorithm” shown at the top of this article: hash with MulSwapMul, then radix sort using [diverting LSD](https://axelle.me/2022/04/19/diverting-lsd-sort/) [radix sort](https://en.wikipedia.org/wiki/Radix_sort). I fuse hashing with the first pass of radix sort, and counting with the last pass of radix sort, for a small additional speedup.

## When should I choose hash tables versus hashed radix sort?

Some hash-table uses cannot be reformulated as hashed radix sort; the latter is more restrictive. Converting hash-table lookups/inserts to hashed radix sort fundamentally requires *batching*: you must issue many lookups without needing results until much later. Sometimes you can turn a one-pass algorithm (traverse a data structure and look up as you go) into two passes of the data structure: first gather keys from the data structure; do the radix sort; then traverse the data structure again to write results back. In some scenarios, such as [hash consing](https://en.wikipedia.org/wiki/Hash_consing), [common subexpression elimination](https://en.wikipedia.org/wiki/Common_subexpression_elimination), or parser lookup tables, the requirement for batching is a dealbreaker: sorting isn’t viable.

Where batching *is* viable, hashed radix sorts are typically viable:

- Any key types usable with hash tables work with hashed radix sorts: apply the same hash.
- If you are *constructing* a hash table, the analog is building a sorted array by radix sort. If you are *querying* an existing table, the analog is: sort the queries, then do a linear-time merge with the existing sorted array of keys.
- Radix sort [parallelizes at least as well](https://reiner.org/#appendix-4-parallelism) as hash tables, if not better.

If hashed radix sorts are viable for your problem, will they be faster? The main determining factor seems to be the number of *repeat accesses per unique key*. If you perform many more inserts/lookups than there are unique keys, hash tables tend to win; if accesses are on the same order as unique keys—most keys touched only a few times—radix sort tends to win. This is because hash tables use O(unique keys) memory, while radix sort uses O(accesses); fitting into a smaller footprint often yields better memory-system performance.

On my benchmarks, hash tables start to pull ahead when keys are accessed ~30 times on average. The threshold rises with problem size:

| Size | 8 accesses per key   HashSet | 8 accesses per key   Hashed sorting | 32 accesses per key   HashSet | 32 accesses per key   Hashed sorting | 128 accesses per key   HashSet | 128 accesses per key   Hashed sorting |
| --- | --- | --- | --- | --- | --- | --- |
| 8 KiB | **1.9 µs** | 6.1 µs | **1.9 µs** | 6.6 µs | **1.7 µs** | 7.2 µs |
| 256 KiB | 125 µs | **119 µs** | **120 us** | 141 µs | **149 µs** | 157 µs |
| 8 MiB | 6.7 ms | **6.1 ms** | **5.7 ms** | 7.0 ms | **5.1 ms** | 7.1 ms |
| 256 MiB | 414 ms | **246 ms** | **240 ms** | **242 ms** | **200 ms** | 267 ms |
| 2 GiB | 3.9 s | **2.6 s** | 3.2 s | **2.7 s** | **2.5 s** | 2.7 s |

## Why does it matter?

Several high-performance systems have an inner loop equivalent to this; I’ve personally worked on two.

First, extremely sparse unstructured matrix multiplication with e.g. sparsity of one in a billion and one scalar per nonzero. This applies to [Google’s Sibyl](https://www.bigdatawire.com/2014/07/17/inside-sibyl-googles-massively-parallel-machine-learning-platform/), which in 2015 was one of Google’s largest workloads and consumed several percent of fleetwide CPU. I and many others collectively spent years optimizing these inner loops.

Second, the [BigCrush test suite for random number generators](https://www-labs.iro.umontreal.ca/~simul/testu01/tu01.html) counts duplicates among n-grams of generated numbers to find anomalies.

In my experience the default for problems like these is hash tables. The surprise to me, once I ran these benchmarks, is that radix sort can beat them by a substantial margin.

---

There’s a rich literature and set of libraries for fast radix sort. I primarily relied on and recommend [diverting LSD sort](https://axelle.me/2022/04/19/diverting-lsd-sort/), [diverting fast radix](https://arxiv.org/pdf/2207.14334), and the Rust library [voracious\_radix\_sort](https://docs.rs/voracious_radix_sort/latest/voracious_radix_sort/). The main characteristics of high-performance implementations like these are listed below:

Use a *diverting* radix sort, which only performs a few passes of radix sort before falling back to insertion sort. If $\text{radix}$ is the number of buckets per pass (e.g., 1024), then after $p$ passes the array has been sorted into $\text{radix}^p$ buckets, with each bucket still needing sorting. After enough passes the buckets are tiny (average size <1), so you stop doing radix passes and fix up locally with insertion sort. This makes diverting radix sort $O(n \log_{\text{radix}} n)$ , versus non-diverting radix sort’s $O(n \cdot w)$ where $w$ is word length. For large keys like uint64 you can typically save more than half the passes.

Form the histograms for all $p$ passes of radix sort in a single histogramming sweep, rather than one by one before each pass. This saves bandwidth: you only do $p+1$ instead of $2p$ sweeps through memory.

Beyond the above techniques standard in the literature, I did two other optimizations.

First, I fused the hashing pass (before the sort) into the histogramming pass (first step of the sort) to save memory bandwidth.

I fall back to inlined insertion sort rather than a function call into the standard library. Calling into standard library sort, which needs to perform many branches on size to figure out that this is a very small array, adds a lot of overhead for buckets whose average size is 1. Inlined insertion sort finishes very quickly for small arrays.

We prefer radix sort because it makes $\log_{1024}(n)$ passes through memory rather than quicksort/mergesort’s $\log_{2}(n)$ passes. Another way to reduce passes is *multi-way mergesort*: merge $k$ arrays at once instead of 2, best implemented with a [tournament tree](https://en.wikipedia.org/wiki/K-way_merge_algorithm#Tournament_Tree).

I implemented and benchmarked this. In my implementation it substantially underperforms quicksort and radix sort. Even though memory bandwidth usage is better, the instruction usage seems to be worse. However, especially here, where the literature appears sparser, it’s possible that my implementation was poorly tuned.

Our tuned hash tables outperform baseline “Swiss Table” hash tables by up to 3× on this workload, largely because we can optimize for our specific case (huge tables, uint64 keys, prioritizing runtime time over memory footprint) whereas Swiss Tables must balance many use cases (strings, small tables, memory footprint).

Our tuned hash table is different than Swiss Tables in the following ways.

*Single table vs. metadata+data.* Swiss Tables keep a “metadata” table (1-byte tags derived from 7-bit hash codes) in addition to the real data table. They probe metadata first (using SIMD instructions to probe 8–16 keys at once), then they probe the data table on a match. This allows efficient probing even when probe sequences are long, it has the disadvantage of requiring *two* cache misses per lookup: one for the metadata table, one for the data table. By contrast, we only use a data table: probing uint64 keys is already plenty fast. This allows us to pay just one cache miss per lookup.

Swiss Table probing is not cacheline-aligned. A probe sequence may start in the middle of a cache line and continue to the next before finishing the current line, wasting bandwidth. Our tuned table also starts probing mid-line, but when we hit the end of the cache line we wrap to the beginning and probe the rest of the cache line before advancing to the next.

Swiss Tables pack their data more densely than our table does: they target a max load factor of 78.5%, whereas we target 50%. This is a pure time-vs-memory tradeoff: Swiss Tables value memory more, we value time more. By using a lower load factor, we keep probe distances shorter, and increase the probability that a lookup can succeed with just one cache miss.

We use [prefetching instructions](https://doc.rust-lang.org/std/intrinsics/fn.prefetch_read_data.html) when accessing the table; Rust’s Swiss Tables implementation does not offer such functionality. Prefetching for hash tables is advanced user functionality, because users need to restructure their loops (and typically split into a loop prologue, loop body, loop epilogue) to support prefetching. Compared to any other API offered by Rust’s HashSet, this functionality is hugely more niche, and perhaps appropriately is not included in the standard library. That said, if you are willing to put in the effort to restructure your loops and tune them, prefetching can offer a huge speedup.

Unlike the above differences, the hash function itself is the same between our tuned hash table and Swiss Tables: we use MulSwapMul in both. This is similar speed to `foldhash::fast` and hugely faster than Rust’s default `SipHash`.

All of these differences together add up to a ~3× speedup over Swiss Tables on this workload:

| Data size | Swiss table | Tuned hash table |
| --- | --- | --- |
| 8 KiB | 3.8 µs | 1.6 µs |
| 256 KiB | 219 µs | 193 µs |
| 8 MiB | 8.1 ms | 7.1 ms |
| 256 MiB | 875 ms | 269 ms |
| 2 GiB | 7.6 s | 2.6 s |

In many high-performance applications we want parallelism. Both radix sort and hash tables parallelize efficiently: for radix sort, parallelize within each pass and synchronize at pass boundaries; for hash tables, use fine-grained locking such as a lock per cacheline inside the table itself.

From a theoretical analysis I expect both radix sort and hash tables to parallelize very well, and the advantage of radix sort to be sustained even in the parallel context. I benchmarked a few of the top Rust libraries for parallel radix sort and parallel hash tables, but I didn’t build any custom tuned versions myself.

For radix sort, I found [voracious\_radix\_sort](https://docs.rs/voracious_radix_sort/latest/voracious_radix_sort/) to have excellent parallel performance; it starts beating the best single-threaded implementation once the data exceeded 8MiB, and I suspect it could be improved further by porting over some of the single-threaded tuning work I did.

| Data size | Best sequential sorting | Parallel sorting (8 cores) |
| --- | --- | --- |
| 8 KiB | 6.5 µs | 109 µs |
| 256 KiB | **92 µs** | 386 µs |
| 8 MiB | **3.9 ms** | 4.5 ms |
| 256 MiB | 185 ms | **61 ms** |
| 2 GiB | 1.9 s | **440 ms** |

For hash tables, I didn’t find an implementation that outperforms my best single-threaded implementation. This surprises me: in other contexts I’ve seen near-linear parallel speedups with a lock-per–cache-line design, and I suspect it’s possible here too. I didn’t spend long tuning this, and it’s possible I was using the existing libraries wrong or outside of their target workload profile.

---

[^1]: For batch algorithms with balanced lookups and inserts.

[^2]: I also ran on a large AMD Zen 4 machine (AMD EPYC 9B14), and got similar results:

[^3]: Traditional radix sorts wouldn’t take 3 passes, they’d take 8: one per byte of an 8-byte key. That’s wasteful: if you’re processing only $2^{32}$ elements, then after 4 passes the array is almost fully sorted (each bucket has, on average, one element), so that’s a good time to fall back to a simpler, cache-local algorithm such as insertion sort. The best form of this approach seems to be [Diverting LSD radix sort](https://axelle.me/2022/04/19/diverting-lsd-sort/).

[^4]: In one pass, radix sort maintains 1024 write pointers (one per bucket). We write a uint64 to one of the write pointers, then advance the write pointer by 8 bytes. To hit ideal cache performance, you want the current cache line for each pointer to be kept in L1 cache (“hot”). Then, when the write pointer advances to the next cache line, we want the previous cache line to be flushed to main memory and then keep the next cache line hot. This requires the CPU to keep 1024 specific cache lines hot, and then quickly evicted and replaced with different cachelines when the pointers advance beyond the current line. Current CPUs typically have capacity for around 2048 cache lines in L1 cache, so in principle this is possible. Unfortunately, CPU caches are hardware-managed rather than software-managed, so we can’t just *tell* the CPU to do this: instead, we rely on its cache eviction policy heuristics to do the job. Sometimes they will make mistakes, causing us to waste memory traffic; the fact that our cacheline demand is a large fraction of the total CPU cache size makes mistakes more likely.

For comparison, on hash tables there’s much less guesswork required from the cache system. To hit the ideal cache system performance, the primary goal is to ensure that many cache misses can run in parallel so that we’re cache-miss-throughput-bound (memory bandwidth) rather than cache-miss-latency-bound (memory latency). We achieve this by issuing cacheline prefetch instructions 64 iterations in advance of performing the lookup, so that we can have 64 cacheline fetches outstanding in parallel. This comes much closer to ideal than for radix sort because (a) there’s CPU prefetch instructions that let us *tell* the cache system what we want to happen and (b) we only need 64 cache lines hot (out of an available 2048) rather than 1024, so mistakes are much less likely.

[^5]: Meta’s [F14 table](https://engineering.fb.com/2019/04/25/developer-tools/f14/) places 14 metadata slots and 14 data slots side by side on the same pair of cache lines, achieving both locality *and* SIMD probing. At that sizing it still needs two (adjacent) misses; a 7-slot variant would be ideal for uint64 keys.

[^6]: A simpler way to make probing cacheline-aligned would be to *start* all probe sequences at the beginning of a cache line. However, this increases average probe length: two different keys are more likely to start at the same probe location, since there are fewer probe sequence starting locations available.