---
title: The Microarchitecture Level
date created: Saturday, April 26th 2025, 7:52:38 pm
date modified: Saturday, July 26th 2025, 2:15:52 pm
---

# The Microarchitecture Level

Prev: [the-digital-logic-level](the-digital-logic-level.md)
Next: [the-instruction-set](the-instruction-set.md)


# Chapter 4 - Structured Computer Organization - Problems

## Section 4.7

### 1.
In Fig. 4-2, one way for producing A as ALU output is shown. Give another way.

### 2.
In the Mic-1, it takes 1 nsec to set up MIR, 1 nsec to gate a register onto the B bus, 3 nsec to run the ALU and shifter, and 1 nsec for the results to propagate back to the registers. The clock pulse width is 2 nsec. Can this machine run at 100 MHz? How about 150 MHz?

### 3.
In Fig. 4-6, the B bus register is encoded in a 4-bit field, but the C bus is represented as a bit map. Why?

### 4.
In Fig. 4-6 there is a box labeled "High bit." Give a circuit diagram for it.

### 5.
When the JMPC field in a microinstruction is enabled, MBR is ORed with NEXT_ADDRESS to form the address of the next microinstruction. Are there any circumstances in which it makes sense to have NEXT_ADDRESS be 0x1FF and use JMPC?

### 6.
Suppose that in the example of Fig. 4-14(a) the statement

```java
i = 0;
```

is added after the if statement. What would the new assembly code be? Assume that the compiler is an optimizing compiler.

### 7.
Give two different IJVM translations for the following Java statement:

```java
i = j + k + 4;
```

### 8.
Give the Java statement that produced the following IJVM code:

```
ILOAD j
ILOAD k
ISUB
BIPUSH 6
ISUB
DUP
IADD
ISTORE i
```

---

### 9.
In the text we mentioned that when translating the statement

```java
if (Z) goto L1; else goto L2
```

to binary, L2 has to be in the bottom 256 words of the control store. Would it not be equally possible to have L1 at, say, 0x040 and L2 at 0x140? Explain your answer.

### 10.
In the microprogram for Mic-1, in it if_icmpeq3, MDR is copied to H and in the next line TOS is subtracted from it. Surely it is better to have one statement here:

```
if_icmpeq3
Z = MDR - TOS; rd
```

Why is this not done?

### 11.
How long does a 200-MHz Mic-1 take to execute the Java statement

```java
i = j + k;
```

Give your answer in nanoseconds.

### 12.
Repeat the previous question, only now for a 200 MHz Mic-2. Based on this calculation, how long would a program that runs for 100 sec on the Mic-1 take on the Mic-2.

### 13.
On the full JVM machine, there are special 1-byte opcodes for loading locals 0 through 3 onto the stack instead of using the general ILOAD instruction. How should IJVM be modified to make the best use of these IJVM instructions?

### 14.
The instruction ISHR (arithmetic shift right integer) exists in JVM but not in IJVM. It shifts the two top values on the stack, replacing the two with a single value, the result. The second from top word of the stack is the operand to be shifted. Its content is shifted right by a value between 0 and 31, inclusive, depending on the value of the 5 least significant bits of the top word on the stack (the other 27 bits of the top word are ignored). The sign bit is replicated to the right for as many bits as the shift count. The opcode for ISHR is 122 (0x7A).

a. What is the arithmetic operation equivalent to shifting right with a count of 2?  
b. Extend the microcode to include this instruction as a part of IJVM.

### 15.
The instruction ISHL (shift left integer) exists in JVM but not in IJVM. It uses the top two values on the stack, replacing the two with a single value, the result. The second from top word of the stack is the operand to be shifted. Its content is shifted left by a value between 0 and 31, inclusive, depending on the value of the 5 least significant bits of the top word on the stack (the other 27 bits of the top word are ignored). Zeros are shifted in from the right for as many bits as the shift count. The opcode for ISHL is 120 (0x78).

a. What is the arithmetic operation equivalent to shifting right with a count of 2?  
b. Extend the microcode to include this instruction as a part of IJVM.

### 16.
The JVM INVOKEVIRTUAL instruction needs to know how many parameters it has. Why?

### 17.
Write microcode for the Mic-1 to implement the JVM POPTWO instruction. This instruction removes two words from the top of the stack.

---

### 18.
Implement the JVM DLOAD instruction for the Mic-2. It has a 1-byte index and pushes the local variable at this position onto the stack. Then it pushes the next higher word onto the stack as well.

### 19.
Draw a finite state machine for tennis scoring. The rules of tennis are as follows. To win, you need at least four points and you must have at least two points more than your opponent. Start with a state (0, 0) indicating that at least no one has scored yet. Then add a state (1, 0) meaning that A has scored. Label the arc from (0, 0) to (1, 0) with A. Now add a state (0, 1) indicating that B has scored, and label the arc from (0, 0) to (0, 1) with B. Continue adding states and arcs until all the possible states have been included.

### 20.
Reconsider the previous problem. Are there any states that could be collapsed without changing the result of any game? If so, which ones are equivalent?

### 21.
Draw a finite state machine for branch prediction that is more tenacious than Fig. 4-42. It should only change predictions after three consecutive mispredictions.

### 22.
The shift register of Fig. 4-27 has a maximum capacity of 6 bytes. Could a cheaper version of the IFU be built with a 5-byte shifter register? How about a 4-byte one?

### 23.
Having examined cheaper IFUs in the previous question, now let us examine more expensive ones. Would there ever be any point to have a much larger shift register in it, say 12 bytes? Why or why not?

### 24.
In the microprogram for the Mic-2, the code for if_icmpeq6 goes to T when Z is set to 1. However, the code for T is the same as goto1. Would it have been possible to go to goto1 directly? Would doing so have made the machine faster?

### 25.
In the Mic-4, the decoding unit maps the IJVM opcode onto the ROM index where the corresponding micro-operations are stored. It would seem to be simpler to just omit the decoding stage and feed the IJVM opcode into the queueing directly. It could use the IJVM opcode as an index into the ROM, the same way as the Mic-1 works. What is wrong with this plan?

### 26.
A computer has a two-level cache. Suppose that 80% of the memory references hit on the first level cache, 15% hit on the second level, and 5% miss. The access times are 5 nsec, 15 nsec, and 60 nsec, respectively, where the times for the level 2 cache and memory start counting at the moment it is known that they are needed (e.g., a level 2 cache access does not even start until the level 1 cache miss occurs). What is the average access time?

### 27.
At the end of Sec. 4.5.1, we said that write allocation wins only if there are likely to be multiple writes to the same cache line in a row. What about the case of a write followed by multiple reads? Would that not also be a big win?

### 28.
In the first draft of this book, Fig. 4-39 showed a three-way associative cache instead of a four-way associative cache. One of the reviewers threw a temper tantrum, claiming that students would be horribly confused by this because three is not a power of two and computers do everything in binary. Since the customer is always right, the figure was changed to a four-way associative cache. Was the reviewer right? Discuss your answer.

---

### 29.
A computer with a five-stage pipeline deals with conditional branches by stalling for the next three cycles after hitting one. How much does stalling hurt the performance if 20% of all instructions are conditional branches? Ignore all sources of stalling except conditional branches.

### 30.
Suppose that a computer prefetches up to 20 instructions in advance. However, on the average, four of these are conditional branches, each with a probability of 90% of being predicted correctly. What is the probability that the prefetching is on the right track?

### 31.
Suppose that we were to change the design of the machine used in Fig. 4-43 to have 16 registers instead of 8. Then we change I6 to use R8 as its destination. What happens in the cycles starting at cycle 6?

### 32.
Normally, dependences cause trouble with pipelined CPUs. Are there optimizations that can be done with WAW dependences that might actually improve matters? What?

### 33.
Rewrite the Mic-1 interpreter but having LV now point to the first local variable instead of to the link pointer.

### 34.
Write a simulator for a 1-way direct mapped cache. Make the number of entries and the line size parameters of the simulation. Experiment with it and report on your findings.


Prev: [the-digital-logic-level](the-digital-logic-level.md)
Next: [the-instruction-set](the-instruction-set.md)
