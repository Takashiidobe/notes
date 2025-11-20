---
title: Processes and Threads
date created: Sunday, July 27th 2025, 4:00:14 pm
date modified: Sunday, July 27th 2025, 4:21:10 pm
---

# Processes and Threads

Prev: [introduction](books/modern-operating-systems/introduction.md)
Next: [deadlocks](deadlocks.md)


1. **In Fig. 2-2, three process states are shown. In theory, with three states, there could be six transitions, two out of each state. However, only four transitions are shown. Are there any circumstances in which either or both of the missing transitions might occur?**

2. **Suppose that you were to design an advanced computer architecture that did process switching in hardware, instead of having interrupts. What information would the CPU need? Describe how the hardware process switching might work.**

3. **On all current computers, at least part of the interrupt handlers are written in assembly language. Why?**

4. **When an interrupt or a system call transfers control to the operating system, a kernel stack area separate from the stack of the interrupted process is generally used. Why?**

5. **In the text it was stated that the model of Fig. 2-6(a) was not suited to a file server using a cache in memory. Why not? Could each process have its own cache?**

6. **In Fig. 2-7 the register set is listed as a per-thread rather than a per-process item. Why? After all, the machine has only one set of registers.**

7. **If a multithreaded process forks, a problem occurs if the child gets copies of all the parent's threads. Suppose that one of the original threads was waiting for keyboard input. Now two threads are waiting for keyboard input, one in each process. Does this problem ever occur in single-threaded processes?**

8. **In Fig. 2-10, a multithreaded Web server is shown. If the only way to read from a file is the normal blocking read system call, do you think user-level threads or kernel-level threads are being used for the Web server? Why?**

9. **Why would a thread ever voluntarily give up the CPU by calling `thread_yield`? After all, since there is no periodic clock interrupt, it may never get the CPU back.**

10. **Can a thread ever be preempted by a clock interrupt? If so, under what circumstances? If not, why not?**

11. **In this problem you are to compare reading a file using a single-threaded file server and a multithreaded server. It takes 15 msec to get a request for work, dispatch it, and do the rest of the necessary processing, assuming that the data needed are in the block cache. If a disk operation is needed, as is the case one-third of the time, an additional 75 msec is required, during which time the thread sleeps. How many requests/sec can the server handle if it is single threaded? If it is multithreaded?**

12. **In the text, we described a multithreaded Web server, showing why it is better than a single-threaded server and a finite-state machine server. Are there any circumstances in which a single-threaded server might be better? Give an example.**

13. **In the discussion on global variables in threads, we used a procedure `create_global` to allocate storage for a pointer to the variable, rather than the variable itself. Is this essential, or could the procedures work with the values themselves just as well?**

14. **Consider a system in which threads are implemented entirely in user space, with the run-time system getting a clock interrupt once a second. Suppose that a clock interrupt occurs while some thread is executing in the run-time system. What problem might occur? Can you suggest a way to solve it?**

15. **Suppose that an operating system does not have anything like the select system call to see in advance if it is safe to read from a file, pipe, or device, but it does allow alarm clocks to be set that interrupt blocked system calls. Is it possible to implement a threads package in user space under these conditions? Discuss.**

16. **Can the priority inversion problem discussed in Sec. 2.3.4 happen with user-level threads? Why or why not?**

17. **In a system with threads, is there one stack per thread or one stack per process when user-level threads are used? What about when kernel-level threads are used? Explain.**

18. **What is a race condition?**

19. **When a computer is being developed, it is usually first simulated by a program that runs one instruction at a time. Even multiprocessors are simulated strictly sequentially like this. Is it possible for a race condition to occur when there are no simultaneous events like this?**

20. **Does the busy waiting solution using the turn variable (Fig. 2-20) work when the two processes are running on a shared-memory multiprocessor, that is, two CPUs, sharing a common memory?**

21. **Does Peterson’s solution to the mutual exclusion problem shown in Fig. 2-21 work when process scheduling is preemptive? How about when it is nonpreemptive?**

22. **Consider a computer that does not have a TSL instruction but does have an instruction to swap the contents of a register and a memory word in a single indivisible action. Can that be used to write a routine `enter_region` such as the one in Fig. 2-22?**

23. **Give a sketch of how an operating system that can disable interrupts could implement semaphores.**

24. **Show how counting semaphores (i.e., semaphores that can hold an arbitrary value) can be implemented using only binary semaphores and ordinary machine instructions.**

25. **If a system has only two processes, does it make sense to use a barrier to synchronize them? Why or why not?**

26. **In Sec. 2.3.4, a situation with a high-priority process, H, and a low-priority process, L, was described, which led to H looping forever. Does the same problem occur if round-robin scheduling is used instead of priority scheduling? Discuss.**

27. **Can two threads in the same process synchronize using a kernel semaphore if the threads are implemented by the kernel? What if they are implemented in user space? Assume that no threads in any other processes have access to the semaphore. Discuss your answers.**

28. **Synchronization within monitors uses condition variables and two special operations, wait and signal. A more general form of synchronization would be to have a single primitive, `waituntil`, that had an arbitrary Boolean predicate as parameter. Thus, one could say, for example:**

```c
waituntil x < 0 || y + z < n
```

**The signal primitive would no longer be needed. This scheme is clearly more general than that of Hoare or Brinch Hansen, but it is not used. Why not? _Hint_: Think about the implementation.**

29. **A fast food restaurant has four kinds of employees: (1) order takers, who take customers’ orders; (2) cooks, who prepare the food; (3) packaging specialists, who stuff the food into bags; and (4) cashiers, who give the bags to customers and take their money. Each employee can be regarded as a communicating sequential process. What form of interprocess communication do they use? Relate this model to processes in UNIX.**

30. **Suppose that we have a message-passing system using mailboxes. When sending to a full mailbox or trying to receive from an empty one, a process does not block. Instead, it gets an error code back. The process responds to the error code by just trying again, over and over, until it succeeds. Does this scheme lead to race conditions?**

31. **In the solution to the dining philosophers problem (Fig. 2-20), why is the state variable set to HUNGRY in the procedure `take_forks`?**

32. **Consider the procedure `put_forks` in Fig. 2-20. Suppose that the variable `state[i]` was set to THINKING after the two calls to `test`, rather than before. How would this change affect the solution?**

33. **The readers and writers problem can be formulated in several ways with regard to which category of processes can be started when. Carefully describe three different variations of the problem, each one favoring (or not favoring) some category of processes. For each variation, specify what happens when a reader or a writer becomes ready to access the database, and what happens when a process is finished using the database.**

34. **The CDC 6600 computers could handle up to 10 I/O processes simultaneously using an interesting form of round-robin scheduling called _processor sharing_. A process switch occurred after each instruction, so instruction 1 came from process 1, instruction 2 came from process 2, etc. The process switching was done by special hardware, and the overhead was zero. If a process needed 7 sec to complete in the absence of competition, how much time would it need if processor sharing was used with _n_ processes?**

35. **Round-robin schedulers normally maintain a list of all runnable processes, with each process occurring exactly once in the list. What would happen if a process occurred twice in the list? Can you think of any reason for allowing this?**

36. **Can a measure of whether a process is likely to be CPU bound or I/O bound be determined by analyzing source code? How can this be determined at run time?**

37. **In the section “When to Schedule,” it was mentioned that sometimes scheduling could be improved if an important process could play a role in selecting the next process to run when it blocks. Give a situation where this could be used and explain how.**

38. **Measurements of a certain system have shown that the average process runs for a time _T_ before blocking on I/O. A process switch requires a time _S_, which is effectively wasted (overhead). For round-robin scheduling with quantum _Q_, give a formula for the CPU efficiency for each of the following:**

- (a) $Q = \infty$  
- (b) $Q > T$  
- (c) $S < Q < T$  
- (d) $Q = S$  
- (e) $Q$ nearly 0  

39. **Five jobs are waiting to be run. Their expected run times are 9, 6, 3, 5, and X. In what order should they be run to minimize average response time? (Your answer will depend on X.)**

40. **Five batch jobs A through E, arrive at a computer center at almost the same time. They have estimated running times of 10, 6, 2, 4, and 8 minutes. Their (externally determined) priorities are 3, 5, 2, 1, and 4, respectively, with 5 being the highest priority. For each of the following scheduling algorithms, determine the mean process turnaround time. Ignore process switching overhead.**

- (a) Round robin.  
- (b) Priority scheduling.  
- (c) First-come, first-served (run in order 10, 6, 2, 4, 8).  
- (d) Shortest job first.  

41. **A process running on CTSS needs 30 quanta to complete. How many times must it be swapped in, including the very first time (before it has run at all)?**

42. **Can you think of a way to save the CTSS priority system from being fooled by random carriage returns?**

43. **The aging algorithm with $a = 1/2$ is being used to predict run times. The previous four runs, from oldest to most recent, are 40, 20, 40, and 15 msec. What is the prediction of the next time?**

44. **A soft real-time system has four periodic events with periods of 50, 100, 200, and 250 msec each. Suppose that the four events require 35, 20, 10, and _x_ msec of CPU time, respectively. What is the largest value of _x_ for which the system is schedulable?**

45. **Explain why two-level scheduling is commonly used.**

46. **Consider a system in which it is desired to separate policy and mechanism for the scheduling of kernel threads. Propose a means of achieving this goal.**

47. **Write a shell script that produces a file of sequential numbers by reading the last number in the file, adding 1 to it, and then appending it to the file. Run one instance of the script in the background and one in the foreground, each accessing the same file. How long does it take before a race condition manifests itself? What is the critical region? Modify the script to prevent the race (_hint_: use `ln file file.lock` to lock the data file).**

48. **Assume that you have an operating system that provides semaphores. Implement a message system. Write the procedures for sending and receiving messages.**

49. **Solve the dining philosophers problem using monitors instead of semaphores.**

50. **Suppose that a university wants to show off how politically correct it is by applying the U.S. Supreme Court’s “Separate but equal is inherently unequal” doctrine to gender as well as race, ending its long-standing practice of gender-segregated bathrooms on campus. However, as a concession to tradition, it decides that when a woman is in a bathroom, other women may enter, but no men, and vice versa. A sign with a sliding marker on the door of each bathroom indicates which of three possible states it is currently in:**

- Empty  
- Women present  
- Men present

**In your favorite programming language, write the following procedures: `woman_wants_to_enter`, `man_wants_to_enter`, `woman_leaves`, `man_leaves`. You may use whatever counters and synchronization techniques you like.**

51. **Rewrite the program of Fig. 2-20 to handle more than two processes.**

52. **Write a producer-consumer problem that uses threads and shares a common buffer. However, do not use semaphores or any other synchronization primitives to guard the shared data structures. Just let each thread access them when it wants to. Use sleep and wakeup to handle the full and empty conditions. See how long it takes for a fatal race condition to occur. For example, you might have the producer print a number once in a while. Do not print more than one number every minute because the I/O could affect the race conditions.**

53. **A process can be put into a round-robin queue more than once to give it a higher priority. Running multiple instances of a program each working on a different part of a data pool can have the same effect. First write a program that tests a list of numbers for primality. Then devise a method to allow multiple instances of the program to run at once in such a way that no two instances of the program will work on the same number. Can you in fact get through the list faster by running multiple copies of the program? Note that your results will depend upon what else your computer is doing; on a personal computer running only instances of this program you would not expect an improvement, but on a system with other processes, you should be able to grab a bigger share of the CPU this way.**


Prev: [introduction](books/modern-operating-systems/introduction.md)
Next: [deadlocks](deadlocks.md)
