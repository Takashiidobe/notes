---
title: The Assembly Language Level
date created: Saturday, April 26th 2025, 7:52:38 pm
date modified: Sunday, July 27th 2025, 8:24:15 am
---

# The Assembly Language Level

Prev: [the-operating-system](the-operating-system.md)
Next: [parallel-computer-architectures](parallel-computer-architectures.md)

## 1.
For a certain program, 1% of the code accounts for 50% of the execution time. Compare the following three strategies with respect to programming time and execution time. Assume that it would take 100 man-months to write it in C, and that assembly code is 10 times harder to write and four times more efficient.

a. Entire program in C.  
b. Entire program in assembler.  
c. First all in C, then the key 1% rewritten in assembler.

## 2.
Do the considerations that hold for two-pass assemblers also hold for compilers?

a. Assume that the compilers produce object modules, not assembly code.  
b. Assume that the compilers produce symbolic assembly language.

## 3.
Suggest a way to allow assembly language programmers to define synonyms for opcodes. How could this be implemented?

You could compile your own assembly first, thus bolting on higher level features. GNU's assembly has high level features but it all lowers to the same assembly at the end.

## 4.
All the assemblers for the Intel CPUs have the destination address as the first operand and the source address as the second operand. What problems would have to be solved to do it the other way?

AT&T is the other way, I assume there's not much difference.

## 5.
Can the following program be assembled in two passes? EQU is a pseudoinstruction that equates the label to the expression in the operand field.

```
A EQU B  
B EQU C  
C EQU D  
D EQU 4
```

## 6.
The Dirtcheap Software Company is planning to produce an assembler for a computer with a 48-bit word. To keep costs down, the project manager, Dr. Scrooge, has decided to limit the length of allowed symbols so that each symbol can be stored in a single word. Scrooge has declared that symbols may consist only of letters, except the letter Q, which is forbidden (to demonstrate their concern for efficiency to the customers). What is the maximum length of a symbol? Describe your encoding scheme.

So we allow for 25 characters.

We want to store a symbol of length $L$, where each character is one of 25 letters, in a 48-bit word. That means the total number of possible symbols is $25^L$, and we want:

$$
25^L \leq 2^{48}
$$

Taking the base-2 logarithm of both sides:

$$
L \cdot \log_2(25) \leq 48
$$

Solving for $L$:

$$
L \leq \frac{48}{\log_2(25)}
$$

Since $\log_2(25) \approx 4.643856$, we get:

$$
L \leq \frac{48}{4.643856} \approx 10.33
$$

The maximum integer value of $L$ is:

$$
\boxed{L = 10}
$$

## 7.
What is the difference between an instruction and a pseudoinstruction?

## 8.
What is the difference between the instruction location counter and the program counter, if any? After all, both keep track of the next instruction in a program.

The instruction location counter is for writing assembly -- the program counter is a hardware register that keeps track of the next instruction in a program at runtime.

## 9.
Show the symbol table after the following Pentium II statements have been encountered. The first statement is assigned to address 1000.

```
EVEREST:    POP BX          (1 BYTE)  
K2:         PUSH BP         (1 BYTE)  
WHITNEY:    MOV BP,SP       (2 BYTES)  
MCKINLEY:   PUSH X          (3 BYTES)  
FUJI:       PUSH SI         (1 BYTE)  
KIBO:       SUB SI,300      (3 BYTES)
```

---

## 10.
Can you envision circumstances in which an assembly language permits a label to be the same as an opcode (e.g., `MOV` as a label)? Discuss.

You could allow `MOV` as a label as long as the executing backend knows that mov as an opcode can only come first, and the destination/source are labeled as such.

## 11.
Show the steps needed to look up Berkeley using binary search on the following list:

Ann Arbor, Berkeley, Cambridge, Eugene, Madison, New Haven, Palo Alto, Pasadena, Santa Cruz, Stony Brook, Westwood, and Yellow Springs.  

When computing the middle element of a list with an even number of elements, use the element just after the middle index.

## 12.
Is it possible to use binary search on a table whose size is prime?

## 13.
Compute the hash code for each of the following symbols by adding up the letters (A = 1, B = 2, etc.) and taking the result modulo the hash table size. The hash table has 19 slots, numbered 0 to 18.

```
els, jan, jelle, maaike
```

Does each symbol generate a unique hash value? If not, how can the collision problem be dealt with?

## 14.
The hash coding method described in the text links all the entries having the same hash code together on a linked list. An alternative method is to have only a single resident table, with each table slot having room for one key and its value (or pointers to them). If the hashing algorithm generates a slot that is already full, a second hashing algorithm is used to try again. If that one is also full, another is used, and so on, until an empty is found. If the fraction of the slots that are full is R, how many probes will be needed, on the average, to enter a new symbol?

## 15.
As technology progresses, it may one day be possible to put thousands of identical CPUs on a chip, each CPU having a few words of local memory. If all CPUs can read and write three shared registers, how can an associative memory be implemented?

## 16.
The Pentium II has a segmented architecture, with multiple independent segments. An assembler for this machine might well have a pseudoinstruction `SEG N` that would direct the assembler to place subsequent code and data in segment N. Does this scheme have any influence on the ILC?

## 17.
Programs often link to multiple DLLs. Would it not be more efficient just to put all the procedures in one big DLL and then link to it?

It could be more efficient in some ways -- you only need to link to one dll which makes programming with routines more convenient, less file handles open, and better optimization across functions (LTO). But, you'd have increased memory usage from having to map a larger DLL, and maintenance and security would be terrible, since you could easily break one routine and that could cause cascading effects on the rest of the routines. If one routine has a security vulnerability, patching that requires patching the whole DLL, and programs would have to manually bump their versions to get that -- but with so many programs using code, you'd still have to support out of data versions, even if the fix could be trivial otherwise.

## 18.
Can a DLL be mapped into two process' virtual address spaces at different virtual addresses? If so, what problems arise? Can they be solved? If not, what can be done to eliminate them?

DLLs can be mapped into two different processes at two different address spaces. This is normal nowadays for security reasons (ASLR, PIC). This also imposes some runtime overhead because absolute relocations have to be turned to relative ones per process, but this overhead for security is considered worth it, as many OSes do this by default these days.

## 19.
One way to do (static) linking is as follows. Before scanning the library, the linker builds a list of procedures needed, that is, names defined as EXTERN in the modules being linked. Then the linker goes through the library linearly, extracting every procedure that is in the list of names needed. Does this scheme work? If not, why not and how can it be remedied?

## 20.
Can a register be used as the actual parameter in a macro call? How about a constant? Why or why not?

---

## 21.
You are to implement a macro assembler. For aesthetic reasons, your boss has decided that macro definitions need not precede their calls. What implications does this decision have on the implementation?

## 22.
Think of a way to put a macro assembler into an infinite loop.

## 23.
A linker reads five modules, whose lengths are 200, 800, 600, 500, and 700 words, respectively. If they are loaded in that order, what are the relocation constants?

## 24.
Write a symbol table package consisting of two routines: `enter(symbol, value)` and `lookup(symbol, value)`. The former enters new symbols in the table and the latter looks them up. Use some form of hash coding.

## 25.
Write a simple assembler for the Mac-1 computer of Chap. 4. In addition to handling the machine instructions, provide a facility for assigning constants to symbols at assembly time, and a way to assemble a constant into a machine word.

## 26.
Add a simple macro facility to the assembler of the preceding problem.


Prev: [the-operating-system](the-operating-system.md)
Next: [parallel-computer-architectures](parallel-computer-architectures.md)
