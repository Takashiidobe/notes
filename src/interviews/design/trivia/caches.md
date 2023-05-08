# How do caches work on your computer?

on x86, cache lines are 64-bytes, and look like the following:

| Type | Size | Latency     | Throughput |
|------|------|-------------| -----------|
| L1   | 64KB | 1 cycle     | 1TB/s+     |
| L2   | 9MB  | 10 cycles   | 1TB/s      |
| L3   | 12MB | 50 cycles   | 400GB/s    |
| RAM  | 32GB | 200 cycles  | 25-100GB/s |
| SSD  | 2TB  | 3000 cycles | 5GB/s      |
| HDD  | 16TB | 1.5M cycles | 200MB/s    |

There are also caches for the Translation Lookaside Buffer (TLB) which are 1024 pages.

Caching is used to make memory accesses faster: in the table above, you can see that smaller caches are much faster, but slower memory can store more memory.

Caches are associative (shared between cores), so they might not be as large per core as you might expect (this computer have 1MB+ of cache, but 12 cores can access it, so they all have to share it).
