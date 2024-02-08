# Memory Speed

## Reading and Writing

Stats from a Western Digital SN750, rated at 3400 MB/s sequential read, 2900 MB/s sequential write.
Only reading with io_uring comes close to using the full bandwidth of the SSD on read, while still being fairly slow on write.

Fsync also seems to have a lot of overhead when using `write()` and `aio_write()` (causing a 3x slowdown), but far less overhead with `io_uring` (20% overhead on sequential writes, 50% overhead on random writes).

- synchronous sequential write - fsync (1MB bs): 248 ops/s, (248MB/s)
- synchronous sequential write - fsync (256KB bs): ~2.4k ops/s, (623MB/s)
- synchronous sequential write + fsync: ~850 ops/s, (222MB/s)
- synchronous random write - fsync: ~2.4k ops/s, (644MB/s)
- synchronous random write + fsync: ~800 ops/s, (214MB/s)
- synchronous sequential read: ~2.9k ops/s, (757MB/s)
- synchronous random read: ~2.2k ops/s, (575MB/s)
- asynchronous sequential write - fsync: ~2.3k ops/s, (599MB/s)
- asynchronous sequential write + fsync: ~800 ops/s, (212MB/s)
- asynchronous random write - fsync: ~2.3k ops/s, (592MB/s)
- asynchronous random write + fsync: ~800 ops/s, (217MB/s)
- asynchronous sequential read: ~3k ops/s, (763MB/s)
- asynchronous random read: ~2.1k ops/s, (561MB/s)
- io_uring sequential write - fsync: ~2.8k ops/s, (723MB/s)
- io_uring sequential write + fsync: ~2.5k ops/s, (653MB/s)
- io_uring random write - fsync: ~3.3k ops/s, (872MB/s)
- io_uring random write + fsync: ~2.4k ops/s, (639MB/s)
- io_uring sequential read: ~15k ops/s, (3876MB/s)
- io_uring random read: ~7.5k ops/s, (1997MB/s)

## Fsync Latency

On the same SSD: ~660μs per fsync, so 1380 fsyncs/second.

On an external SSD, closer to 460 fsyncs/second, or about ~2ms per fsync, so 3x slower.

## Databases

### Sqlite3

- With Journal Mode WAL and Normal Synchronous (Durable)

```sh
./sqlite-bench -batch-count 1000 -batch-size 1000 -row-size 1000 -journal-mode wal -synchronous normal ./bench.db
Inserts:   1000000 rows
Elapsed:   7.824s
Rate:      127817.265 insert/sec
File size: 1026584576 bytes
```

```sh
./sqlite-bench -batch-count 1000000 -batch-size 1 -row-size 1000 -journal-mode wal -synchronous normal ./bench.db
Inserts:   1000000 rows
Elapsed:   43.839s
Rate:      22810.910 insert/sec
File size: 1026584576 bytes
```

- With Journal Mode WAL and trusting the OS to handle syncs (Unsafe)

```sh
./sqlite-bench -batch-count 1000 -batch-size 1000 -row-size 1000 -journal-mode wal -synchronous off ./bench.db
Inserts:   1000000 rows
Elapsed:   4.752s
Rate:      210432.225 insert/sec
File size: 1026584576 bytes
```

```sh
./sqlite-bench -batch-count 1000000 -batch-size 1 -row-size 1000 -journal-mode wal -synchronous off ./bench.db
Inserts:   1000000 rows
Elapsed:   28.624s
Rate:      34936.319 insert/sec
File size: 1026584576 bytes
```

### RocksDB

Load 10M keys sequentially into database

```
Set seed to 1684413524204146 because --seed was 0
Initializing RocksDB Options from the specified file
Initializing RocksDB Options from command-line flags
Integrated BlobDB: blob cache disabled
Keys:       16 bytes each (+ 0 bytes user-defined timestamp)
Values:     800 bytes each (400 bytes after compression)
Entries:    10000000
Prefix:    0 bytes
Keys per prefix:    0
RawSize:    7782.0 MB (estimated)
FileSize:   3967.3 MB (estimated)
Write rate: 0 bytes/second
Read rate: 0 ops/second
Compression: Snappy
Compression sampling rate: 0
Memtablerep: SkipListFactory
Perf Level: 1
------------------------------------------------
Initializing RocksDB Options from the specified file
Initializing RocksDB Options from command-line flags
Integrated BlobDB: blob cache disabled
DB path: [./db]
fillseq      :       5.288 micros/op 189094 ops/sec 52.883 seconds 10000000 operations;  147.2 MB/s
Microseconds per write:
Count: 10000000 Average: 5.2883  StdDev: 128.83
Min: 4  Median: 4.7066  Max: 406752
Percentiles: P50: 4.71 P75: 5.57 P99: 9.89 P99.9: 24.10 P99.99: 49.45
```

Reading 10M keys in database in random order

```
Set seed to 1684412888948042 because --seed was 0
Initializing RocksDB Options from the specified file
Initializing RocksDB Options from command-line flags
Integrated BlobDB: blob cache disabled
Keys:       16 bytes each (+ 0 bytes user-defined timestamp)
Values:     800 bytes each (400 bytes after compression)
Entries:    10000000
Prefix:    0 bytes
Keys per prefix:    0
RawSize:    7782.0 MB (estimated)
FileSize:   3967.3 MB (estimated)
Write rate: 0 bytes/second
Read rate: 0 ops/second
Compression: Snappy
Compression sampling rate: 0
Memtablerep: SkipListFactory
Perf Level: 1
------------------------------------------------
DB path: [./db]
readrandom   :       4.215 micros/op 3779991 ops/sec 42.328 seconds 160000000 operations;  294.2 MB/s (1000335 of 10000000 found)

Microseconds per read:
Count: 160000000 Average: 4.2148  StdDev: 21.70
Min: 0  Median: 0.7457  Max: 44209
Percentiles: P50: 0.75 P75: 1.50 P99: 44.33 P99.9: 74.35 P99.99: 329.00
```
Overwriting 10M keys in database in random order

```
Set seed to 1684413619666146 because --seed was 0
Initializing RocksDB Options from the specified file
Initializing RocksDB Options from command-line flags
Integrated BlobDB: blob cache disabled
Keys:       16 bytes each (+ 0 bytes user-defined timestamp)
Values:     800 bytes each (400 bytes after compression)
Entries:    10000000
Prefix:    0 bytes
Keys per prefix:    0
RawSize:    7782.0 MB (estimated)
FileSize:   3967.3 MB (estimated)
Write rate: 0 bytes/second
Read rate: 0 ops/second
Compression: Snappy
Compression sampling rate: 0
Memtablerep: SkipListFactory
Perf Level: 1
------------------------------------------------
DB path: [./db]
overwrite    :       8.553 micros/op 116913 ops/sec 85.534 seconds 10000000 operations;   91.0 MB/s
Microseconds per write:
Count: 10000000 Average: 8.5534  StdDev: 2.73
Min: 4  Median: 8.1227  Max: 4990
Percentiles: P50: 8.12 P75: 9.34 P99: 14.97 P99.9: 30.69 P99.99: 50.85
```

Read while writing 1M keys in database in random order

```
Set seed to 1684411784145181 because --seed was 0
Initializing RocksDB Options from the specified file
Initializing RocksDB Options from command-line flags
Integrated BlobDB: blob cache disabled
RocksDB:    version 7.8.3
Date:       Thu May 18 08:09:44 2023
CPU:        16 * 12th Gen Intel(R) Core(TM) i5-1240P
CPUCache:   12288 KB
Keys:       16 bytes each (+ 0 bytes user-defined timestamp)
Values:     800 bytes each (800 bytes after compression)
Entries:    1000000
Prefix:    0 bytes
Keys per prefix:    0
RawSize:    778.2 MB (estimated)
FileSize:   778.2 MB (estimated)
Write rate: 0 bytes/second
Read rate: 0 ops/second
Compression: Snappy
Compression sampling rate: 0
Memtablerep: SkipListFactory
Perf Level: 1
------------------------------------------------
DB path: [./db]
readwhilewriting :      20.477 micros/op 769319 ops/sec 20.798 seconds 16000000 operations;  598.7 MB/s (1000000 of 1000000 found)

Microseconds per read:
Count: 16000000 Average: 20.4782  StdDev: 109.17
Min: 1  Median: 13.5473  Max: 40204
Percentiles: P50: 13.55 P75: 18.12 P99: 187.27 P99.9: 814.39 P99.99: 5044.78
```

## HTTP Server Benchmark

~200k RPS for an HTTP server.

```
Running 5s test @ http://localhost:3000
  256 goroutine(s) running concurrently
975712 requests in 4.929485946s, 105.15MB read
Requests/sec:		197933.82
Transfer/sec:		21.33MB
Avg Req Time:		1.293361ms
Fastest Request:	21.095µs
Slowest Request:	67.116949ms
Number of Errors:	0
```

## Redis Benchmark

~200k RPS for insert/set/delete.

```
====== PING_INLINE ======
  100000 requests completed in 0.54 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 186915.88 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.142     0.040     0.135     0.231     0.375     1.415
====== PING_MBULK ======
  100000 requests completed in 0.52 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 193798.45 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.141     0.032     0.127     0.263     0.391     1.655
====== SET ======
  100000 requests completed in 0.53 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 187265.92 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.141     0.032     0.135     0.207     0.335     1.055
====== GET ======
  100000 requests completed in 0.54 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 184501.84 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.143     0.032     0.135     0.239     0.367     1.575
====== INCR ======
  100000 requests completed in 0.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 194931.77 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.140     0.032     0.127     0.255     0.399     1.815
====== LPUSH ======
  100000 requests completed in 0.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 194174.77 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.135     0.072     0.127     0.207     0.319     1.095
====== RPUSH ======
  100000 requests completed in 0.52 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 193423.59 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.140     0.040     0.127     0.263     0.383     3.407
====== LPOP ======
  100000 requests completed in 0.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 194931.77 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.136     0.064     0.127     0.199     0.367     1.527
====== RPOP ======
  100000 requests completed in 0.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 194174.77 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.137     0.032     0.127     0.207     0.359     2.055
====== SADD ======
  100000 requests completed in 0.52 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 190839.70 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.137     0.064     0.135     0.199     0.343     0.967
====== HSET ======
  100000 requests completed in 0.51 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 194552.53 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.137     0.040     0.127     0.215     0.359     0.999
====== SPOP ======
  100000 requests completed in 0.52 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 191570.88 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.140     0.032     0.135     0.247     0.359     1.199
====== ZADD ======
  100000 requests completed in 0.55 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 183486.23 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.145     0.040     0.135     0.231     0.407     1.191
====== ZPOPMIN ======
  100000 requests completed in 0.53 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 189753.31 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.141     0.032     0.127     0.255     0.367     1.279
====== LPUSH (needed to benchmark LRANGE) ======
  100000 requests completed in 0.52 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 192307.70 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.140     0.032     0.127     0.239     0.375     2.647
====== LRANGE_100 (first 100 elements) ======
  100000 requests completed in 0.90 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 110864.74 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.235     0.112     0.231     0.335     0.495     1.759
====== LRANGE_300 (first 300 elements) ======
  100000 requests completed in 2.40 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 41666.66 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.609     0.200     0.599     0.767     1.023     3.127
====== LRANGE_500 (first 500 elements) ======
  100000 requests completed in 3.58 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 27932.96 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.911     0.168     0.887     1.135     1.575     4.071
====== LRANGE_600 (first 600 elements) ======
  100000 requests completed in 4.11 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 24360.54 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        1.038     0.216     1.015     1.279     1.839     4.575
====== MSET (10 keys) ======
  100000 requests completed in 0.50 seconds
  50 parallel clients
  3 bytes payload
  keep alive: 1
  host configuration "save": 3600 1 300 100 60 10000
  host configuration "appendonly": no
  multi-thread: no

Summary:
  throughput summary: 198019.80 requests per second
  latency summary (msec):
          avg       min       p50       p95       p99       max
        0.161     0.040     0.143     0.271     0.391     1.495
```

## Networks

- Net read/write TCP: ~500k ops/s (15.1Gbit/s)

## System

Caches:

| Type | Size | Latency     | Throughput |
|------|------|-------------| -----------|
| L1   | 64KB | 3 cycles    | 4TB/s      |
| L2   | 9MB  | 10 cycles   | 1.5TB/s    |
| L3   | 12MB | 40 cycles   | 400GB/s    |
| RAM  | 32GB | 200 cycles  | 25GB/s     |
| SSD  | 2TB  | 3000 cycles | 5GB/s      |
| HDD  | 16TB | 1.5M cycles | 200MB/s    |

- Mutex lock/unlock, no context switch: (6ns)
- System call: (114.8ns)
- Process context switch: (~2.5μs)
- Thread context switches w/ futex: (~2.2μs)
- Thread context switches w/ sched_yield: (~374.2ns)

## Hashing

- sha3-256:          56.14 MiB/sec
- md5:              404.15 MiB/sec
- sha1:             432.36 MiB/sec
- xxhash:          1827.80 MiB/sec
- murmur3:         1826.07 MiB/sec
- jhash:           1542.84 MiB/sec
- fnv:             3720.28 MiB/sec
- crc32c:          4682.73 MiB/sec

## Historical

- 8-track tape (1960s-1980s): ~100B/s (Read-only)
- Cassette Tape (1970s-1980s): ~50B/s (Read-only)
- IBM 3420 magnetic tape drive (1985): ~1MB/s
- CD Drive (1980s-1990s): 150KB/s (1X) - 3.6MB/s (24X) (Read-only)
- Floppy Disk (1980s-1990s): ~100kb/s (R/W)
- USB Drive (2000s): ~20MB/s (R/W)
- HDD Drive (2000s): ~120MB/s @ 7200rps (R/W)
