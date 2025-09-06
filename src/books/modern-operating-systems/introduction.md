---
title: Introduction
date created: Sunday, July 27th 2025, 4:00:14 pm
date modified: Sunday, July 27th 2025, 4:17:15 pm
---

# Introduction

Next: [processes-and-threads](processes-and-threads.md)


1. What are the two main functions of an operating system?

2. What is multiprogramming?

3. What is spooling? Do you think that advanced personal computers will have spooling as a standard feature in the future?

4. On early computers, every byte of data read or written was directly handled by the CPU (i.e., there was no DMA). What implications does this organization have for multiprogramming?

5. Why was timesharing not widespread on second-generation computers?

6. The family of computers idea was introduced in the 1960s with the IBM System/360 mainframes. Is this idea now dead as a doornail or does it live on?

7. One reason GUIs were initially slow to be adopted was the cost of the hardware needed to support them. How much video RAM is needed to support a 25 line × 80 row character monochrome text screen? How much for a 1024 × 768 pixel 24-bit color bitmap? What was the cost of this RAM at 1980 prices ($5/KB)? How much is it now?

For a 25 x 80 char monochrome text screen, you'd need just the 1 byte per character, since if the byte is > 0, it would be on, otherwise, it would be off. An 80 x 25 requires 2000 bytes, so in 1980 prices, this would be 2KB of RAM, or $10. For a 1024 x 768 pixel display, you'd require about 800K bytes, and since colors are 3 bytes for RGB, you multiply by 3 bytes, so 2.4M bytes of memory. This would be more than $10k USD, which is extreme. In 2025, RAM is far cheaper. It costs about $2/GB for DDR4 or so, so to use a monitor with 1024 x 768, it would cost you less than a cent.

8. Which of the following instructions should be allowed only in kernel mode?
   (a) Disable all interrupts.  
   (b) Read the time-of-day clock.  
   (c) Set the time-of-day clock.  
   (d) Change the memory map.
   
a) Disabling interrupts should be done in privileged mode, because if users could do it they would disable interrupts and drop interrupts for other processes.
b) Reading the time of day clock is fine for users to do.
c) Setting the clock should be privileged since other processes use it so the kernel should mediate access.
d) Changing the memory map is also something only the kernel should be able to do, since it would be a security hazard if users could do it.

9. List some differences between personal computer operating systems and mainframe operating systems.

10. A computer has a pipeline with four stages. Each stage takes the same time to do its work, namely, 1 nsec. How many instructions per second can this machine execute?

11. An alert reviewer notices a consistent spelling error in the manuscript of an operating systems textbook that is about to go to press. The book has approximately 700 pages, each with 50 lines of 80 characters each. How long will it take to electronically scan the text in the case of the master copy being in each of the levels of memory of Fig. 1-7? For internal storage methods, consider that the access time given is per character, for disk devices assume the time is per block of 1024 characters, and for tape assume the time given is to the start of the data with subsequent access at the same speed as disk access.

12. In Fig. 1-9, the MMU compares the incoming (virtual) address to the limit register, causing a fault if it is too large. An alternative design would be to first add the virtual address to the base register and then compare the result to the (physical) address in the limit register. Are the two methods logically equivalent? Are they equivalent in performance?

13. When a user program makes a system call to read or write a disk file, it provides an indication of which file it wants, a pointer to the data buffer, and the count. Control is then transferred to the operating system, which calls the appropriate driver. Suppose that the driver starts the disk and terminates until an interrupt occurs. In the case of reading from the disk, obviously the caller will have to wait until the data are available (no data for it). What about the case of writing to the disk? Need the caller be blocked awaiting completion of the disk transfer?

14. What is the key difference between a trap and an interrupt?

15. A computer uses the relocation scheme of Fig. 1-9(a). A program is 10,000 bytes long and is loaded at address 40,000. What values do the base and limit register get according to the scheme described in the text?

16. Why is the process table needed in a timesharing system? Is it also needed in personal computer systems in which only one process exists, that process taking over the entire machine until it is finished?

17. Is there any reason why you might want to mount a file system on a nonempty directory? If so, what is it?

18. For each of the following system calls, give a condition that causes it to fail: fork, exec, and unlink.

19. Can the

```c
count = write(fd, buffer, nbytes);
```

call return any value in `count` other than `nbytes`? If so, why?

20. A file whose file descriptor is `fd` contains the following sequence of bytes: 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5. The following system calls are made:

```c
lseek(fd, 3, SEEK_SET);
read(fd, &buffer, 4);
```

where the `lseek` call makes a seek to byte 3 of the file. What does `buffer` contain after `read` has completed?

The 4 bytes after byte 3, so 5, 9, 2, 6

21. What is the essential difference between a block special file and a character special file? Which one is more important?

22. In the example given in Fig. 1-17, the library procedure is called `read` and the system call itself is called `read`. Is it essential that both of these have the same name? If not, which one is more important?

23. The client-server model is popular in distributed systems. Can it also be used in a single-computer system?

24. To a programmer, a system call looks like any other call to a library procedure. Is it important that a programmer know which library procedures result in system calls? Under what circumstances and why?

25. Figure 1-23 shows that a number of UNIX system calls have no Win32 API equivalents. For each of the calls listed as having no Win32 equivalent, what are the consequences for a programmer of converting a UNIX program to run under Windows?

26. Here are some questions for practicing unit conversions:

(a) How long is a microyear in seconds?  
(b) Micrometers are often called microns. How long is a gigamicron?  
(c) How many bytes are there in a 1-TB memory?  
(d) The mass of the earth is 6000 yottagrams. What is that in kilograms?

27. Write a shell that is similar to Fig. 1-19 but contains enough code that it actually works so you can test it. You might also add some features such as redirection of input and output, pipes, and background jobs.

28. If you have a personal UNIX-like system (Linux, MINIX, Free BSD, etc.) available that you can safely crash and reboot, write a shell script that attempts to create an unlimited number of child processes and observe what happens. Before running the experiment, type `sync` to the shell to flush the file system buffers to disk to avoid ruining the file system.  
_Note:_ Do not try this on a shared system without first getting permission from the system administrator. The consequences will be instantly obvious so you are likely to be caught and sanctions may follow.

29. Examine and try to interpret the contents of a UNIX-like or Windows directory with a tool like the UNIX `od` program or the MS-DOS `DEBUG` program. _Hint:_ How you do this will depend upon what the OS allows. One trick that may work is to create a directory on a floppy disk with one operating system and then read the raw disk data using a different operating system that allows such access.


Next: [processes-and-threads](processes-and-threads.md)
