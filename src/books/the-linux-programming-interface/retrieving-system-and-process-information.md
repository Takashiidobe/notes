---
title: retrieving-system-and-process-information
---

# Retrieving System and Process Information

Prev: [system-limits-and-options](system-limits-and-options.md) Next: [file-io-buffering](file-io-buffering.md)

## The `/proc` file system

Unix provides the `proc` virtual file system to investigate processes and metadata about them.

### Obtaining Information About a Process: `/proc/PID`

The kernel provides a directory named `/proc/PID` for each process on the system. In the directory are files and subdirectories containing information about the process. For example, if you cat `/proc/1/status`, you can find information about the `init` process.

```
$ cat /proc/1/status
Name: init Name of command run by this process
State: S (sleeping) State of this process
Tgid: 1 Thread group ID (traditional PID, getpid())
Pid: 1 Actually, thread ID (gettid())
PPid: 0 Parent process ID
TracerPid: 0 PID of tracing process (0 if not traced)
Uid: 0 0 0 0 Real, effective, saved set, and FS UIDs
Gid: 0 0 0 0 Real, effective, saved set, and FS GIDs
FDSize: 256 # of file descriptor slots currently allocated
Groups: Supplementary group IDs
VmPeak: 852 kB Peak virtual memory size
VmSize: 724 kB Current virtual memory size
VmLck: 0 kB Locked memory
VmHWM: 288 kB Peak resident set size
VmRSS: 288 kB Current resident set size
VmData: 148 kB Data segment size
VmStk: 88 kB Stack size
VmExe: 484 kB Text (executable code) size
VmLib: 0 kB Shared library code size
VmPTE: 12 kB Size of page table (since 2.6.10)
Threads: 1 # of threads in this thread’s thread group
SigQ: 0/3067 Current/max. queued signals (since 2.6.12)
SigPnd: 0000000000000000 Signals pending for thread
ShdPnd: 0000000000000000 Signals pending for process (since 2.6)
SigBlk: 0000000000000000 Blocked signals
SigIgn: fffffffe5770d8fc Ignored signals
SigCgt: 00000000280b2603 Caught signals
CapInh: 0000000000000000 Inheritable capabilities
CapPrm: 00000000ffffffff Permitted capabilities
CapEff: 00000000fffffeff Effective capabilities
CapBnd: 00000000ffffffff Capability bounding set (since 2.6.26)
Cpus_allowed: 1 CPUs allowed, mask (since 2.6.24)
Cpus_allowed_list: 0 Same as above, list format (since 2.6.26)
Mems_allowed: 1 Memory nodes allowed, mask (since 2.6.24)
Mems_allowed_list: 0 Same as above, list format (since 2.6.26)
voluntary_ctxt_switches: 6998 Voluntary context switches (since 2.6.23)
nonvoluntary_ctxt_switches: 107 Involuntary context switches (since 2.6.23)
Stack usage: 8 kB Stack usage high-water mark (since 2.6.32)
```

Some interesting information in the `/proc` directory includes:

| File    | Description (process attribute)                                             |
|---------|-----------------------------------------------------------------------------|
| cmdline | Command-line arguments delimited by \0                                      |
| cwd     | Symbolic link to current working directory                                  |
| environ | Environment list NAME=value pairs, delimited by \0                          |
| exe     | Symbolic link to file being executed                                        |
| fd      | Directory containing symbolic links to files opened by this process         |
| maps    | Memory mappings                                                             |
| mem     | Process virtual memory (must lseek() to valid offset before I/O)            |
| mounts  | Mount points for this process                                               |
| root    | Symbolic link to root directory                                             |
| status  | Various information (e.g., process IDs, credentials, memory usage, signals) |
| task    | Contains one subdirectory for each thread in process (Linux 2.6)            |

### The `/proc/PID/fd` directory

This directory contains one symbolic link for each file descriptor that the process has open. Any process can access its own `/proc/PID` directory using `/proc/self`.

### Threads: the `/proc/PID/task` directory

Each thread

Prev: [system-limits-and-options](system-limits-and-options.md) Next: [file-io-buffering](file-io-buffering.md)
