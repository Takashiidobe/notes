# System Design

Self-Hosted:

$5 per TB or $0.005 per GB for HDD/SAS.
$50 per TB or $0.05 per GB for SSD.

Cloud:
$10 per TB or $0.01 per GB/Month for HDD/SAS.
$100 per TB or $0.10 per GB/Month for SSD.

## Back of the Envelope Numbers

| Operation                           | Latency                                  | Throughput | 1 MiB  | 1 GiB  |
| ----------------------------------- | ---------------------------------------- | ---------- | ------ | ------ |
| Sequential Memory R/W (64 bytes)    | 0.5 ns                                   |            |        |        |
| \-- Single Thread, No SIMD          |                                          | 10 GiB/s   | 100 μs | 100 ms |
| \-- Single Thread, SIMD             |                                          | 20 GiB/s   | 50 μs  | 50 ms  |
| \-- Threaded, No SIMD               |                                          | 30 GiB/s   | 35 μs  | 35 ms  |
| \-- Threaded, SIMD                  |                                          | 35 GiB/s   | 30 μs  | 30 ms  |
| Hashing, not crypto-safe (64 bytes) | 25 ns                                    | 2 GiB/s    | 500 μs | 500 ms |
| Random Memory R/W (64 bytes)        | 50 ns                                    | 1 GiB/s    | 1 ms   | 1s     |
| Fast Serialization `[8]` `[9]` †    | N/A                                      | 1 GiB/s    | 1 ms   | 1s     |
| Fast Deserialization `[8]` `[9]` †  | N/A                                      | 1 GiB/s    | 1 ms   | 1s     |
| System Call                         | 500 ns                                   | N/A        | N/A    | N/A    |
| Hashing, crypto-safe (64 bytes)     | 500 ns                                   | 200 MiB/s  | 10 ms  | 10s    |
| Sequential SSD read (8 KiB)         | 1 μs                                     | 4 GiB/s    | 200 μs | 200 ms |
| Context Switch `[1] [2]`            | 10 μs                                    | N/A        | N/A    | N/A    |
| Sequential SSD write, -fsync (8KiB) | 10 μs                                    | 1 GiB/s    | 1 ms   | 1s     |
| TCP Echo Server (32 KiB)            | 10 μs                                    | 4 GiB/s    | 200 μs | 200 ms |
| Decompression `[11]`                | N/A                                      | 1 GiB/s    | 1 ms   | 1s     |
| Compression `[11]`                  | N/A                                      | 500 MiB/s  | 2 ms   | 2s     |
| Sequential SSD write, +fsync (8KiB) | 1 ms                                     | 10 MiB/s   | 100 ms | 2 min  |
| Sorting (64-bit integers)           | N/A                                      | 200 MiB/s  | 5 ms   | 5s     |
| Random SSD Seek (8 KiB)             | 100 μs                                   | 70 MiB/s   | 15 ms  | 15s    |
| Serialization `[8]` `[9]` †         | N/A                                      | 100 MiB/s  | 10 ms  | 10s    |
| Deserialization `[8]` `[9]` †       | N/A                                      | 100 MiB/s  | 10 ms  | 10s    |
| Proxy: Envoy/ProxySQL/Nginx/HAProxy | 50 μs                                    | ?          | ?      | ?      |
| Network within same region `[6]`    | 250 μs                                   | 100 MiB/s  | 10 ms  | 10s    |
| {MySQL, Memcached, Redis, ..} Query | 500 μs                                   | ?          | ?      | ?      |
| Random HDD Seek (8 KiB)             | 10 ms                                    | 0.7 MiB/s  | 2 s    | 30m    |
| Network between regions `[6]`       | [Varies](https://www.cloudping.co/grid#) | 25 MiB/s   | 40 ms  | 40s    |
| Network NA East <-> West            | 60 ms                                    | 25 MiB/s   | 40 ms  | 40s    |
| Network EU West <-> NA East         | 80 ms                                    | 25 MiB/s   | 40 ms  | 40s    |
| Network NA West <-> Singapore       | 180 ms                                   | 25 MiB/s   | 40 ms  | 40s    |
| Network EU West <-> Singapore       | 160 ms                                   | 25 MiB/s   | 40 ms  | 40s    |

## Costs

| What        | Amount | $ / Month | $ / Hour |
| ----------- | ------ | --------- | -------- |
| CPU         | 1      | $10       | $0.02    |
| Memory      | 1 GB   | $1        |          |
| SSD         | 1 GB   | $0.1      |          |
| Disk        | 1 GB   | $0.01     |          |
| S3, GCS, .. | 1 GB   | $0.01     |          |
| Network     | 1 GB   | $0.01     |          |

## Compression

| What        | Compression Ratio |
| ----------- | ----------------- |
| HTML        | 2-3x              |
| English     | 2-4x              |
| Source Code | 2-4x              |
| Executables | 2-3x              |
| RPC         | 5-10x             |
| SSL         | \-2% `[10]`       |
