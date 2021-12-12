---
title: "Operating System and Hardware Optimization"
---

# Operating System and Hardware Optimization

Prev: [performance-schema](performance-schema.md)
Next: [optimizing-server-settings](optimizing-server-settings.md)

## What Limits MySQL's Performance?

I/O saturation is much less than common than CPU exhaustion. Memory
exhaustion is more common.

## How to select CPUs for MySQL

- Low latency = fast CPUs
- High throughput = Multiple CPUs

## Balancing Memory and Disk Resources

### Caching, Reads, and Writes

High memory allows for faster reads, since reads don't have to hit disk:
As well, caching is good for writes, because it allows more writes to be
batched before flushing to disk.
As well, various modifications can be modified in memory, and then
minified before being persisted to disk.

This is why most databases persist to a Write-Ahead log, which allows
changes to be made to memory.

## Solid-State Storage

SSDs are standard for most database systems. They allow for much better
random read and write performance, better sequential read and write
performance, and better support for hard drives.

### An Overview of Flash Memory

SSDs are faster for reads, but are much more complex for writes: Cells
can only be rewritten with an erase cycle that wears out the block. As
well, the number of erase cycles a block can tolerate depends on the
underlying technology it uses.

This is mainly dependent on firmware, drivers, etc, which can make
performance worse, and wear leveling and write amplification caused by
moving blocks around wears out SSDs faster than HDDs.

### Garbage Collection

SSDs are much more prone to Garbage Collection pauses, because erase
instructions can take a few milliseconds, compared to a write to disk,
which is a few hundred microseconds.

### RAID performance optimization

| level   | Synopsis                       | Redundancy   | Disks required | Faster reads | Faster writes |
| ------- | ------------------------------ | ------------ | -------------- | ------------ | ------------- |
| RAID 0  | Cheap, fast, dangerous         | No           | N              | Yes          | Yes           |
| RAID 1  | Fast reads, simple, safe       | Yes          | 2 (usually)    | Yes          | No            |
| RAID 5  | Cheap, fast with SSDs          | Yes          | N + 1          | Yes          | Depends       |
| RAID 6  | Like RAID 5 but more resilient | Yes          | N + 2          | Yes          | Depends       |
| RAID 10 | Expensive, fast, safe          | Yes          | 2N             | Yes          | Yes           |
| RAID 50 | For very large data stores     | Yes 2(N + 1) | Yes            | Yes          |

RAID arrays should be heavily monitored, as they can fail in a myriad of
ways, and some failures are more catastrophic than others.

## Network Configuration

A slow network will cripple MySQL performance. DNS is a common problem:
MySQL does a forward and backward resolution, which can be slow.

This can be jumped over with `skip_name_resolve` option. But this only
allows MySQL to be connected to with ip addresses, or localhost.

Sometimes you might need to allow more local ports:

```sh
echo 1024 65535 > /proc/sys/net/ipv4/ip_local_port_range
```

Or allow more connections:

```sh
echo 4096 > /proc/sys/net/ipv4/tcp_max_syn_backl
```

Or change the timeout that comes after closing a socket:

```sh
echo <value> > /proc/sys/net/ipv4/tcp_fin_timeout
```

## Choosing a Filesystem

On Linux, you might be best using a journaling filesystem, like ext4,
XFS, or ZFS.

Make sure to check for the useless options and disable them for each
filesystem.

Here are some tradeoffs:

| Filesystem                  | Operating system            | Journaling | Large directories |
| --------------------------- | --------------------------- | ---------- | ----------------- |
| ext3                        | GNU/Linux                   | Optional   | Optional/partial  |
| ext4                        | GNU/Linux                   | Yes        | Yes               |
| Journaled File System (JFS) | GNU/Linux                   | Yes        | No                |
| NTFS                        | Windows                     | Yes        | Yes               |
| ReiserFS                    | GNU/Linux                   | Yes        | Yes               |
| UFS (Solaris)               | Solaris                     | Yes        | Tunable           |
| UFS (FreeBSD)               | FreeBSD                     | No         | Optional/partial  |
| UFS2                        | FreeBSD                     | No         | Optional/partial  |
| XFS                         | GNU/Linux                   | Yes        | Yes               |
| ZFS                         | GNU/Linux, Solaris, FreeBSD | Yes        | Yes               |

XFS is a good default.

## Choosing a Disk Queue Scheduler

On Linux, the queue scheduler determines the order in which requests to
a block device are actually sent to the underlying device.

The default is `Completely Fair Queueing` or `cfq`, which is good for
laptops and desktops, but poor for servers.

Catting the queue scheduler will highlight the active scheduler in
brackets.

```sh
cat /sys/block/sda/queue/scheduler
noop deadline [cfq]
```

Noop and deadline are about equal in benchmarks. It's just important to
replace [cfq].

## Memory and Swapping

MySQL performs best with a lot of memory to hold as a cache to avoid
disk access. As well, the performance of the allocator can be slow,
(glibmalloc) which can be replaced with `tcmalloc` or `jemalloc`.

Swapping occurs when the operating system writes some virtual memory to
disk because it doesn't have enough physical memory to hold it.

The authors recommend running your MySQL without swap space enabled,
which may lead to process termination, but avoids the slowness of swap.

The default `swappiness` is 60:

```sh
cat /proc/sys/vm/swappiness
60
```

Set it to 0 for servers.

```sh
echo 0 > /proc/sys/vm/swappiness
```

Some other tricks involve using `innodb_flush_method=O_DIRECT` to
relieve I/O pressure or set `memlock` which locks MySQL in memory. This
can cause MySQL to crash if it tries to allocate more memory it doesn't
have though.

## Operating System Status

`iostat`, `vmstat`, and `mpstat` are good tools to read more about the
status of the operating system.

As well, `perf`, the linux profiler, and `strace` is a good way to look
at what uses so much CPU.

Prev: [performance-schema](performance-schema.md)
Next: [optimizing-server-settings](optimizing-server-settings.md)
