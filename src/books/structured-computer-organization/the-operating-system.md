---
title: The Operating System
date created: Saturday, April 26th 2025, 7:52:38 pm
date modified: Saturday, July 26th 2025, 2:23:46 pm
---

# The Operating System

Prev: [the-instruction-set](the-instruction-set.md)
Next: [the-assembly-language-level](the-assembly-language-level.md)

# Chapter 6 - Structured Computer Organization - Problems

## 1.
Why does an operating system interpret only some of the level 3 instructions, whereas a microprogram interprets all the ISA level instructions?

## 2.
A machine has a 32-bit byte-addressable virtual address space. The page size is 8 KB.  
How many pages of virtual address space exist?

## 3.
A virtual memory has a page size of 1024 words, eight virtual pages, and four physical page frames. The page table is as follows:

| Virtual page | Page frame         |
|--------------|--------------------|
| 0            | 3                  |
| 1            | 1                  |
| 2            | not in main memory |
| 3            | not in main memory |
| 4            | 2                  |
| 5            | not in main memory |
| 6            | 0                  |
| 7            | not in main memory |

a. Make a list of all virtual addresses that will cause page faults.  
b. What are the physical addresses for 0, 3728, 1023, 1024, 1025, 7800, and 4096?

## 4.
A computer has 16 pages of virtual address space but only four page frames. Initially, the memory is empty. A program references the virtual pages in the order:

```
0, 7, 2, 7, 5, 8, 9, 2, 4
```

a. Which references cause a page fault with LRU?  
b. Which references cause a page fault with FIFO?

---

## 5.
In Sec. 6.1.3 an algorithm was presented for implementing a FIFO page replacement strategy. Devise a more efficient one. *Hint:* It is possible to update the counter in the newly-loaded page, leaving all the others alone.

## 6.
In the paged systems discussed in the text, the page fault handler was part of the ISA level and thus was not present in any OSM level program’s address space. In reality, the page fault handler also occupies pages and might, under some circumstances (e.g., FIFO page replacement policy), itself be removed. What would happen if the page fault handler were not present when a page fault occurred? How could this be fixed?

## 7.
Not all computers have a hardware bit that is automatically set when a page is written to. Nevertheless, it is useful to keep track of which pages have been modified, to avoid having to assume worst case and write all pages back to the disk after use. Assuming that each page has hardware bits to separately enable access for reading, writing, and execution, how can the operating system keep track of which pages are changed (i.e., which are dirty)?

## 8.
A segmented memory has paged segments. Each virtual address has a 2-bit segment number, a 2-bit page number, and an 11-bit offset within the page. The main memory contains 32 KB, divided into up to 2-KB pages. Each segment is either read-only, read/execute, read/write, or read/write/execute. The page tables and protection are as follows:

| Segment | Page | Frame | State     |
|---------|------|--------|-----------|
| 0       | 0    | 9      | On disk   |
|         | 1    | 3      | 0         |
|         | 3    | 12     | 3         |
| 1       | 1    | 0      | not in    |
|         | 2    | 15     | main mem  |
| 2       | 0    | 1      | 0         |
|         | 2    | 2      | 6         |
| 3       | 1    | 0      | 14        |
|         | 2    | 2      | 6         |
|         | 3    | 3      | On disk   |

For each of the following accesses to virtual memory, tell what physical address is computed. If a fault occurs, tell which kind.

1. fetch data — Segment 0, Page 1, Offset 1  
2. fetch data — Segment 1, Page 1, Offset 10  
3. fetch data — Segment 1, Page 3, Offset 2047  
4. store data — Segment 3, Page 1, Offset 4  
5. store data — Segment 3, Page 1, Offset 2  
6. store data — Segment 3, Page 1, Offset 2  
7. branch to it — Segment 0, Page 0, Offset 14  
8. fetch data — Segment 1, Page 2, Offset 100  
9. fetch data — Segment 2, Page 2, Offset 50  
10. branch to it — Segment 3, Page 0, Offset 60

## 9.
Some computers allow I/O directly to user space. For example, a program could start up a disk transfer to a buffer inside a user process. Does this cause any problems if compaction is used to implement the virtual memory? Discuss.

---
## 10.
Operating systems that allow memory-mapped files always require files be mapped at page boundaries. For example, with 4K pages, a file can be mapped in starting at virtual address 4096, but not starting at virtual address 5000. Why?

## 11.
When a segment register is loaded on the Pentium II, the corresponding descriptor is fetched and loaded into an invisible part of the segment register. Why do you think the Intel designers decided to do this?

## 12.
A program on the Pentium II references local segment 10 with offset 8000. The BASE field of LDT segment 10 contains 10000. Which page directory entry does the Pentium II use? What is the page number? What is the offset?

## 13.
Discuss some possible algorithms for removing segments in an unpaged, segmented memory.

## 14.
Compare internal fragmentation to external fragmentation. What can be done to alleviate each?

## 15.
Supermarkets are constantly faced with a problem similar to page replacement in virtual memory systems. They have a fixed amount of shelf space to display an ever-increasing number of products. If an important new product comes along, say, 100% efficient dog food, some existing product must be dropped from the inventory to make room for it. The obvious replacement algorithms are LRU and FIFO. Which one would you prefer?

## 16.
Why are cache blocks always much smaller than virtual memory pages, often a hundred times smaller?

## 17.
Why do many file systems require that a file be explicitly opened with an open system call before being read?

## 18.
Compare the bit-map and hole-list methods for keeping track of free space on a disk with 800 cylinders, each one having 5 tracks of 32 sectors. How many holes would it take before the hole list would be larger than the bit map? Assume that the allocation unit is the sector and that a hole requires a 32-bit table entry.

## 19.
To be able to make some predictions of disk performance, it is useful to have a model of storage allocation. Suppose that the disk is viewed as a linear address space of N ≫ 1 sectors, consisting of a run of data blocks, then a hole, then another run of data blocks, and so on. If empirical measurements show that the probability distributions for data and hole lengths are the same, with the chance of either being i sectors as 2^−i, what is the expected number of holes on the disk?

## 20.
On a certain computer, a program can create as many files as it needs, and all files may grow dynamically during execution without giving the operating system any advance information about their ultimate size. Do you think that files are stored in consecutive sectors? Explain.

## 21.
Consider the following method by which an operating system might implement semaphore instructions. Whenever the CPU is about to do an up or down on a semaphore (an integer variable in memory), it first sets the CPU priority or mask bits in such a way as to disable all interrupts. Then it fetches the semaphore, modifies it, and branches accordingly. Finally, it enables interrupts again. Does this method work if

a. There is a single CPU that switches between processes every 100 msec?  
b. Two CPUs share a common memory in which the semaphore is located?

---

# Page 480

## 22.
The Nevercrash Operating System Company has been receiving complaints from some of its customers about its latest release, which includes semaphore operations. They feel it is immoral for processes to block (they call it “sleeping on the job”). Since it is company policy to give the customers what they want, it has been proposed to add a third operation, `peek`, to supplement `up` and `down`. `peek` simply examines the semaphore without changing it or blocking the process. In this way, programs that feel it is immoral to block can first inspect the semaphore to see if it is safe to do a `down`. Will this idea work if three or more processes use the semaphore? Why?

## 23.
Make a table showing which of the processes P1, P2, and P3 are running and which are blocked as a function of time from 0 to 1000 msec. All three processes perform up and down instructions on the same semaphore. When two processes are blocked and an up is done, the process with the lower number is restarted, that is, P1 gets preference over P2 and P3, and so on. Initially, all three are running and the semaphore is 1.

```
At t = 100 P1 does a down  
At t = 200 P1 does a down  
At t = 300 P2 does a down  
At t = 400 P3 does a down  
At t = 500 P1 does a down  
At t = 600 P2 does an up  
At t = 700 P2 does a down  
At t = 800 P1 does an up  
At t = 900 P1 does an up
```

## 24.
In an airline reservation system, it is necessary to ensure that while one process is busy using a file, no other process can also use it. Otherwise, two different processes, working for two different ticket agents, might each inadvertently sell the last seat on some flight. Devise a synchronization method using semaphores that makes sure that only one process at a time accesses each file (assuming that the processes obey the rules).

## 25.
To make it possible to implement semaphores on a computer with multiple CPUs that share a common memory, computer architects often provide a Test and Set Lock instruction. TSL X tests the location X. If the contents are zero, they are set to 1 in a single, indivisible memory cycle, and the next instruction is skipped. If it is nonzero, the TSL acts like a no-op. Using TSL it is possible to write procedures `lock` and `unlock` with the following properties. `lock(x)` checks to see if `x` is zero. If not, it locks `x` and returns control. If `x` is already locked, it just waits until it becomes unlocked, then it locks `x` and returns control. `unlock` releases an existing lock. If all processes look at the semaphore table before using it, only one process at a time can fiddle with the variables and pointers, thus preventing races. Write `lock` and `unlock` in assembly language. (Make any reasonable assumptions you need.)

---

# Page 481

## 26.
Show the values of `in` and `out` for a circular buffer of length 65 words after each of the following operations. Both start at 0.

```
a. 22 words are put in  
b. 9 words are removed  
c. 40 words are put in  
d. 17 words are removed  
e. 12 words are put in  
f. 3 words are removed  
g. 8 words are put in  
h. 1 word is removed
```

## 27.
Suppose that a version of UNIX uses 2K disk blocks and stores 512 disk addresses per indirect block (single, double, and triple). What would the maximum file size be? (Assume that file pointers are 64 bits wide.)

## 28.
Suppose that the UNIX system call

```c
unlink("/usr/ast/bin/game3")
```

were executed in the context of Figure 6-37. Describe carefully what changes are made in the directory system.

## 29.
Imagine that you had to implement the UNIX system on a microcomputer where main memory was in short supply. After a considerable amount of shoehorning, it still did not quite fit, so you picked a system call at random to sacrifice for the common good. You picked pipe, which creates the pipes used to send byte streams from one process to another. Is it still possible to implement I/O redirection somehow? What would be the problems and possible solutions?

## 30.
The Committee for Fairness to File Descriptors is organizing a protest against the UNIX system because whenever the latter returns a file descriptor, it always returns the lowest number not currently in use. Consequently, higher-numbered file descriptors are hardly ever used. Their plan is to return the lowest number not yet used by the program rather than the lowest number currently not in use. They claim that it is trivial to implement, will not affect existing programs, and is fairer. What do you think?

## 31.
In NT is it possible to set up an access control list in such a way that Roberta has no access at all to a file, but everyone else has full access to it. How do you think this is implemented?

## 32.
Describe two ways to program producer-consumer problems using shared buffers and semaphores in NT. Think about how to implement the shared buffer in each case.

## 33.
It is common to test out page replacement algorithms by simulation. For this exercise, you are to write a simulator for a page-based virtual memory for a machine with 64 1 KB pages. The simulator should maintain a single table of 64 entries, one per page, containing the physical page number corresponding to that virtual page. The simulator should read in a file containing virtual addresses in decimal, one address per line. If the corresponding page is memory, just record a page hit. If it is not in memory, call a page replacement procedure to pick a page to evict (i.e., an entry in the table to overwrite) and record a page miss. No page transport actually occurs. Generate a file consisting of random addresses and test the performance for both LRU and FIFO. Now generate an address file in which x percent of the addresses are four bytes higher than the previous one (to simulate locality). Run tests for various values of x and report on your results.

---

# Page 482

## 34.
Write a program for UNIX or NT that takes as input the name of a directory. The program should print a list of the files in the directory, one line per file, and after the file name, print the size of the file. **Print** the file names in the order they occur in the directory. Unused slots in the directory should be listed as *(unused)*.


Prev: [the-instruction-set](the-instruction-set.md)
Next: [the-assembly-language-level](the-assembly-language-level.md)
