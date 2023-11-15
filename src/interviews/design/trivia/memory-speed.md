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
------------------------------------------------------
(       3,       4 ]  2961392  29.614%  29.614% ######
(       4,       6 ]  5769853  57.699%  87.312% ############
(       6,      10 ]  1201190  12.012%  99.324% ##
(      10,      15 ]    41125   0.411%  99.736%
(      15,      22 ]    14999   0.150%  99.886%
(      22,      34 ]     8230   0.082%  99.968%
(      34,      51 ]     2433   0.024%  99.992%
(      51,      76 ]      567   0.006%  99.998%
(      76,     110 ]       99   0.001%  99.999%
(     110,     170 ]       39   0.000%  99.999%
(     170,     250 ]       39   0.000% 100.000%
(     250,     380 ]       20   0.000% 100.000%
(     380,     580 ]        5   0.000% 100.000%
(    1900,    2900 ]        1   0.000% 100.000%
(    2900,    4400 ]        3   0.000% 100.000%
(    4400,    6600 ]        3   0.000% 100.000%
(   14000,   22000 ]        1   0.000% 100.000%
(  380000,  570000 ]        1   0.000% 100.000%
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
------------------------------------------------------
[       0,       1 ] 107281798  67.051%  67.051% #############
(       1,       2 ] 25259726  15.787%  82.838% ###
(       2,       3 ]  2895362   1.810%  84.648%
(       3,       4 ]  2543108   1.589%  86.237%
(       4,       6 ]  2390091   1.494%  87.731%
(       6,      10 ]  1447670   0.905%  88.636%
(      10,      15 ]  2769450   1.731%  90.367%
(      15,      22 ]  6410362   4.006%  94.373% #
(      22,      34 ]  6005435   3.753%  98.127% #
(      34,      51 ]  2298089   1.436%  99.563%
(      51,      76 ]   576871   0.361%  99.924%
(      76,     110 ]    60092   0.038%  99.961%
(     110,     170 ]    24378   0.015%  99.977%
(     170,     250 ]    14875   0.009%  99.986%
(     250,     380 ]    11014   0.007%  99.993%
(     380,     580 ]     5221   0.003%  99.996%
(     580,     870 ]     2593   0.002%  99.998%
(     870,    1300 ]     1249   0.001%  99.998%
(    1300,    1900 ]      826   0.001%  99.999%
(    1900,    2900 ]      659   0.000%  99.999%
(    2900,    4400 ]      337   0.000% 100.000%
(    4400,    6600 ]      215   0.000% 100.000%
(    6600,    9900 ]      532   0.000% 100.000%
(    9900,   14000 ]       26   0.000% 100.000%
(   14000,   22000 ]       19   0.000% 100.000%
(   22000,   33000 ]        1   0.000% 100.000%
(   33000,   50000 ]        1   0.000% 100.000%
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
------------------------------------------------------
(       3,       4 ]      404   0.004%   0.004%
(       4,       6 ]   643400   6.434%   6.438% #
(       6,      10 ]  8208743  82.087%  88.525% ################
(      10,      15 ]  1052781  10.528%  99.053% ##
(      15,      22 ]    74116   0.741%  99.794%
(      22,      34 ]    14574   0.146%  99.940%
(      34,      51 ]     5025   0.050%  99.990%
(      51,      76 ]      782   0.008%  99.998%
(      76,     110 ]      125   0.001% 100.000%
(     110,     170 ]       16   0.000% 100.000%
(     170,     250 ]        1   0.000% 100.000%
(     250,     380 ]       30   0.000% 100.000%
(     380,     580 ]        1   0.000% 100.000%
(     870,    1300 ]        1   0.000% 100.000%
(    4400,    6600 ]        1   0.000% 100.000%
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
------------------------------------------------------
[       0,       1 ]       13   0.000%   0.000%
(       1,       2 ]     2093   0.013%   0.013%
(       2,       3 ]    35688   0.223%   0.236%
(       3,       4 ]   167412   1.046%   1.283%
(       4,       6 ]   808517   5.053%   6.336% #
(       6,      10 ]  2486403  15.540%  21.876% ###
(      10,      15 ]  6342635  39.641%  61.517% ########
(      15,      22 ]  4841790  30.261%  91.778% ######
(      22,      34 ]   805031   5.031%  96.810% #
(      34,      51 ]   188910   1.181%  97.991%
(      51,      76 ]    53533   0.335%  98.325%
(      76,     110 ]    30191   0.189%  98.514%
(     110,     170 ]    66102   0.413%  98.927%
(     170,     250 ]    54117   0.338%  99.265%
(     250,     380 ]    54068   0.338%  99.603%
(     380,     580 ]    35823   0.224%  99.827%
(     580,     870 ]    14444   0.090%  99.917%
(     870,    1300 ]     6484   0.041%  99.958%
(    1300,    1900 ]     2453   0.015%  99.973%
(    1900,    2900 ]     1419   0.009%  99.982%
(    2900,    4400 ]     1041   0.007%  99.989%
(    4400,    6600 ]      795   0.005%  99.994%
(    6600,    9900 ]      552   0.003%  99.997%
(    9900,   14000 ]      465   0.003% 100.000%
(   14000,   22000 ]       18   0.000% 100.000%
(   22000,   33000 ]        2   0.000% 100.000%
(   33000,   50000 ]        1   0.000% 100.000%
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
