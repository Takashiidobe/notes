---
title: Debugging
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:09:52 pm
---

# Debugging

- dstat: Prints out how many bytes were written to network/disk
- strace: prints out every system call a program uses.
- opensnoop: `opensnoop -p PID` prints out every file opened by a program in real time.
- netcat: send bytes over a network
- netstat:
- lsof: List processes and ports working
- ngrep: grep through network packets
- tcpdump: dumps packets sent over tcp
- perf: sampling profiler that shows what your program is doing (disassembled)
- flamegraphs: graph what the program is doing
- perf stat: print out counters of what a program does
- tcplife: gives stats on tcp connection lengths on a given port.