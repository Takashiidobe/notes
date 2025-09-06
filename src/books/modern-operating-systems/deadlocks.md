---
title: Deadlocks
date created: Sunday, July 27th 2025, 4:00:14 pm
date modified: Sunday, July 27th 2025, 4:21:15 pm
---

# Deadlocks

Prev: [processes-and-threads](processes-and-threads.md)
Next: [memory-management](memory-management.md)

# Chapter 3: Deadlocks — Modern Operating Systems (2nd Edition)

## Problems

1. **Give an example of a deadlock taken from politics.**

2. **Students working at individual PCs in a computer laboratory send their files to be printed by a server which spools the files on its hard disk. Under what conditions may a deadlock occur if the disk space for the print spool is limited? How may the deadlock be avoided?**

3. **In the preceding question which resources are preemptable and which are nonpreemptable?**

4. **In Fig. 3-1 the resources are returned in the reverse order of their acquisition. Would giving them back in the other order be just as good?**

5. **Fig. 3-3 shows the concept of a resource graph. Do illegal graphs exist, that is graphs that structurally violate the model we have used of resource usage? If so, give an example of one.**

6. **The discussion of the ostrich algorithm mentions the possibility of process table slots or other system tables filling up. Can you suggest a way to enable a system administrator to recover from such a situation?**

7. **Consider Fig. 3-4. Suppose that in step (c) C requested S instead of requesting R. Would this lead to deadlock? Suppose that it requested both S and R?**

8. **At a crossroads with STOP signs on all four approaches, the rule is that each driver yields the right of way to the driver on his right. This rule is not adequate when four vehicles arrive simultaneously. Fortunately, humans are sometimes capable of doing more intelligently than computers and the problem is usually resolved when one driver signals the driver to his left to go ahead. Can you draw an analogy between this behavior and any of the ways of recovering from deadlock described in Sec. 3.4.3? Why is a problem with such a simple solution in the human world so difficult to apply to a computer system?**

9. **Suppose that in Fig. 3-6 $C_{ij} + R_{ij} > E_j$ for some $i$. What implications does this have for all the processes finishing without deadlock?**

10. **All the trajectories in Fig. 3-8 are horizontal or vertical. Can you envision any circumstances in which diagonal trajectories were also possible?**

11. **Can the resource trajectory scheme of Fig. 3-8 also be used to illustrate the problem of deadlocks with three processes and three resources? If so, how can this be done? If not, why not?**

12. **In theory, resource trajectory graphs could be used to avoid deadlocks. By clever scheduling, the operating system could avoid unsafe regions. Suggest a practical problem with actually doing this.**

13. **Take a careful look at Fig. 3-11(b). If D asks for one more unit, does this lead to a safe state or an unsafe one? What if the request came from C instead of D?**

14. **Can a system be in a state that is neither deadlocked nor safe? If so, give an example. If not, prove that all states are either deadlocked or safe.**

15. **A system has two processes and three identical resources. Each process needs a maximum of two resources. Is deadlock possible? Explain your answer.**

16. **Consider the previous problem again, but now with $p$ processes each needing a maximum of $m$ resources and a total of $r$ resources available. What condition must hold to make the system deadlock free?**

17. **Suppose that process A in Fig. 3-12 requests the last tape drive. Does this action lead to a deadlock?**

18. **A computer has six tape drives, with $n$ processes competing for them. Each process may need two drives. For which values of $n$ is the system deadlock free?**

19. **The banker’s algorithm is being run in a system with $m$ resource classes and $n$ processes. In the limit of large $m$ and $n$, the number of operations that must be performed to check a state for safety is proportional to $m^a n^b$. What are the values of $a$ and $b$?**

20. **A system has four processes and five allocatable resources. The current allocation and maximum needs are as follows:**

| Process | Allocated | Maximum | Available |
|---------|-----------|---------|-----------|
| A       | 1 0 2 1 1 | 1 1 2 1 3 |           |
| B       | 2 0 1 1 0 | 2 2 2 1 0 | 0 0 1 1 1 |
| C       | 0 1 1 0 2 | 2 1 3 1 0 |           |
| D       | 1 1 1 1 0 | 1 2 2 2 1 |           |

**What is the smallest value of $x$ for which this is a safe state?**

21. **A distributed system using mailboxes has two IPC primitives, send and receive. The latter primitive specifies a process to receive from and blocks if no message from that process is available, even though messages may be waiting from other processes. There are no shared resources, but processes need to communicate frequently about other matters. Is deadlock possible? Discuss.**

22. **Two processes, A and B, each need three records, 1, 2, and 3, in a database. If A asks for them in the order 1, 2, 3, and B asks for them in the same order, deadlock is not possible. However, if B asks for them in the order 3, 2, 1, then deadlock is possible. With three resources, there are $3!$ or 6 possible combinations each process can request the resources. What fraction of all the combinations are guaranteed to be deadlock free?**

23. **Now reconsider the above problem, but using two-phase locking. Will that eliminate the potential for deadlock? Does it have any other undesirable characteristics, however? If so, which ones?**

24. **In an electronic funds transfer system, there are hundreds of identical processes that work as follows. Each process reads an input line specifying an amount of money, the account to be credited, and the account to be debited. Then it locks both accounts and transfers the money, releasing the locks when done. With many processes running in parallel, there is a very real danger that having locked account $x$ it will be unable to lock $y$ because $y$ has been locked by a process now waiting for $x$. Devise a scheme that avoids deadlocks. Do not release an account record until you have completed the transaction. (In other words, solutions that lock one account and then release it immediately if the other is locked are not allowed.)**

25. **One way to prevent deadlocks is to eliminate the hold-and-wait condition. In the text it was proposed that before asking for a new resource, a process must first release whatever resources it already holds (assuming that is possible). However, doing so introduces the danger that it may get the new resource but lose some of the existing ones to competing processes. Propose an improvement to this scheme.**

26. **A computer science student assigned to work on deadlocks thinks of the following brilliant way to eliminate deadlocks. When a process requests a resource, it specifies a time limit. If the process blocks because the resource is not available, a timer is started. If the time limit is exceeded, the process is released and allowed to run again. If you were the professor, what grade would you give this proposal and why.**

27. **Cinderella and the Prince are getting divorced. To divide their property, they have agreed on the following algorithm. Every morning, each one may send a letter to the other’s lawyer requesting one item of property. Since it takes a day for letters to be delivered, they have agreed that if both discover that they have requested the same item on the same day, the next day they will send a letter canceling the request. Among their property is their dog, Woofer, Woofer’s doghouse, their canary, Tweeter, and Tweeter’s cage. The animals love their houses, so it has been agreed that any division of property separating an animal from its house is invalid, requiring the whole division to start over from scratch. Both Cinderella and the Prince desperately want Woofer. So they can go on (separate) vacations, each spouse has programmed a personal computer to handle the negotiation. When they come back from vacation, the computers are still negotiating. Why? Is deadlock possible? Is starvation possible? Discuss.**

28. **A student majoring in anthropology and minoring in computer science has embarked on a research project to see if African baboons can be taught about deadlocks. He locates a deep canyon and fastens a rope across it, so the baboons can cross hand-over-hand. Several baboons can cross at the same time, provided that they are all going in the same direction. If eastward moving and westward moving baboons both get onto the rope at the same time, a deadlock will result (the baboons will get stuck in the middle) because it is impossible for one baboon to climb over another one when suspended over the canyon. If a baboon wants to cross the canyon, he must check to make sure that no other baboon is currently crossing in the opposite direction. Write a program using semaphores that avoids deadlock. Do not worry about a series of eastward moving baboons holding up the westward moving baboons indefinitely.**

29. **Repeat the previous problem, but now avoid starvation. When a baboon that wants to cross to the east arrives at the rope and finds baboons crossing to the west, he waits until at least one baboon has crossed the other way.**

30. **Program a simulation of the banker’s algorithm. Your program should cycle through each of the bank clients asking for a request and evaluating whether it is safe or unsafe. Output a log of requests and decisions to a file.**



Prev: [processes-and-threads](processes-and-threads.md)
Next: [memory-management](memory-management.md)
