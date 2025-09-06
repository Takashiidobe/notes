---
title: The Instruction Set
date created: Saturday, April 26th 2025, 7:52:38 pm
date modified: Friday, July 25th 2025, 7:57:09 am
---

# The Instruction Set

Prev: [the-microarchitecture-level](the-microarchitecture-level.md)
Next: [the-operating-system](the-operating-system.md)

# Structured Computer Organization - Chapter 5 Problems

## 1.
On the Pentium II, Instructions Can Contain Any Number of Bytes, even or Odd. On the UltraSPARC II, All Instructions Contain an Integral Number of Words, that Is, an even Number of bytes.  
**Give one advantage of the Pentium II scheme.**

Since instructions can contain any number of bytes, they can be variable length. So, the first 128 instructions can be 1 byte, whereas for the sparc, they would have to fit in 2-bytes, thus wasting a byte. However, having more fixed rules allows for better pipelining, so it is a performance for memory tradeoff, since not all instructions will fit in 1 byte anyway, and the SPARC only pays a penalty for instructions that would have an odd parity compared to the pentium, which would always pay a penalty.

---

## 2.
Design an expanding opcode to allow all the following to be encoded in a 36-bit instruction:

- 7 instructions with two 15-bit addresses and one 3-bit register number  
- 500 instructions with one 15-bit address and one 3-bit register number  
- 50 instructions with no addresses or registers

1. This can be encoded by having 0-3 bits for the instructions, 3-33 bits for the addresses, and 33-36 bits for register number (0-7).
2. This can be encoded with 0-9 bits for the instructions ($log_2{500} \lt 9$), 9-24 bits for the address, and 24-27 for the register number.
3. Can have $log_2{50} \lt 6$ bits, so bits 0-6 could be used.

---

## 3.
Is it possible to design an expanding opcode to allow the following to be encoded in a 12-bit instruction? A register is 3 bits.

- 4 instructions with 3 registers  
- 255 instructions with one register  
- 16 instructions with zero registers  

1. $log_2{4} = 2$, and $3 \times 3 = 9$ bits for the registers, so yes, 11 bits.
2. $log_2{255} \approxeq 8$ and one register is 3 bits, so yes, 11 bits.
3. $log_2{16} \approxeq 4$ so yes, 4 bits.

---

## 4.
A certain machine has 16-bit instructions and 6-bit addresses. Some instructions have one address and others have two.  
If there are $n$ two-address instructions, what is the maximum number of one-address instructions?

For two address instructions, you have to use up 12 bits for the addresses. Thus, you have 16 opcodes left. If there are $n$ of these addresses, then you can only have $16 - n$ for the single address instructions.

---

## 5.
Given the memory values below and a one-address machine with an accumulator, what values do the following instructions load into the accumulator?

**Memory contents:**

| Address | Value |     |
| ------- | ----- | --- |
| word 20 | 40    |     |
| word 30 | 50    |     |
| word 40 | 60    |     |
| word 50 | 70    |     |

**Instructions:**
- a. `LOAD IMMEDIATE 20`  
- b. `LOAD DIRECT 20`  
- c. `LOAD INDIRECT 20`  
- d. `LOAD IMMEDIATE 30`  
- e. `LOAD DIRECT 30`  
- f. `LOAD INDIRECT 30`

| Instruction          | Accumulator Value | Explanation                        |
| -------------------- | ----------------- | ---------------------------------- |
| a. LOAD IMMEDIATE 20 | 20                | Loads the literal value 20         |
| b. LOAD DIRECT 20    | 40                | Loads the value at address 20      |
| c. LOAD INDIRECT 20  | 60                | 20 → 40 → load value at address 40 |
| d. LOAD IMMEDIATE 30 | 30                | Loads the literal value 30         |
| e. LOAD DIRECT 30    | 50                | Loads the value at address 30      |
| f. LOAD INDIRECT 30  | 70                | 30 → 50 → load value at address 50 |

---

## 6.
Compare 0-, 1-, 2-, and 3-address machines by writing programs to compute:  
$$
X = \frac{(A + B \times C)}{(D - E \times F)}
$$

The instructions available for each machine are as follows:

### Instruction Set Table:

| 0 Address | 1 Address | 2 Address       | 3 Address       |
| --------- | --------- | --------------- | --------------- |
| PUSH M    | LOAD M    | MOV (X = Y)     | MOV (X = Y)     |
| POP M     | STORE M   | ADD (X = X + Y) | ADD (X = Y + Z) |
| ADD       | ADD M     | SUB (X = X − Y) | SUB (X = Y − Z) |
| SUB       | SUB M     | MUL (X = X × Y) | MUL (X = Y × Z) |
| MUL       | MUL M     | DIV (X = X / Y) | DIV (X = Y / Z) |
| DIV       | DIV M     |                 |                 |

1-address machine:

```
PUSH C         ; stack: C
PUSH B         ; stack: B, C
MUL            ; stack: B*C
PUSH A         ; stack: A, (B*C)
ADD            ; stack: A + B*C

PUSH F         ; stack: F
PUSH E         ; stack: E, F
MUL            ; stack: E*F
PUSH D         ; stack: D, (E*F)
SUB            ; stack: D - E*F

DIV            ; (A + B*C) / (D - E*F)
POP X          ; store result in X
```

2-address machine:

```
LOAD C         ; AC = C
MUL B          ; AC = B * C
ADD A          ; AC = A + B * C
STORE TEMP1    ; TEMP1 = A + B * C

LOAD F         ; AC = F
MUL E          ; AC = E * F
SUB D          ; AC = D - E * F
STORE TEMP2    ; TEMP2 = D - E * F

LOAD TEMP1     ; AC = A + B * C
DIV TEMP2      ; AC = (A + B * C) / (D - E * F)
STORE X
```

3-address machine:

```
MUL T1, B, C     ; T1 = B * C
ADD T2, A, T1    ; T2 = A + B * C

MUL T3, E, F     ; T3 = E * F
SUB T4, D, T3    ; T4 = D - E * F

DIV X, T2, T4    ; X = (A + B * C) / (D - E * F)
```

---

## 7.
Devise an addressing mechanism that allows an arbitrary set of 64 addresses, not necessarily contiguous, in a large address space to be specifiable in a 6-bit field.

Make an array, since $log_2{64} = 6$, so since the addresses are non-contiguous, have them index into an array where the actual address itself is stored.

---

## 8.
Give a disadvantage of self-modifying code that was not mentioned in the text.

---

## 9.
Convert the following formulas from infix to reverse Polish notation:

- a. `A + B + C + D + E`
- b. `(A + B) × (C + D) + E `
- c. `(A × (B + C) + D) + E`
- d. `(A − B) × ((C − D × E) / F) / G × H`

---

## 10.
Convert the following reverse Polish notation formulas to infix:

- a. A B + C D + ×  
- b. A B C D + × +  
- c. A B C D E × × × +  

---

## 11.
Which of the following pairs of reverse Polish notation formulas are mathematically equivalent?

- a. `A B + C +` and `A B C + +`  
- b. `A B − C −` and `A B C − −`  
- c. `A B × C +` and `A B C + ×`  

---

## 12.
Write three reverse Polish notation formulas that cannot be converted to infix.

---

## 13.
Convert the following infix Boolean formulas to reverse Polish notation:

- a. (A AND B) OR C  
- b. (A OR B) AND (A OR C)  
- c. (A AND B) OR (C AND D)  

---

## 14.
Convert the following infix formula to reverse Polish notation and generate JVM code to evaluate it:

$$
(2 × 3 + 4) − (4 / 2 + 1)
$$

---

## 15.
The assembly language instruction

> MOV REG, ADDR


means load a register from memory on the Pentium II. However, on the UltraSPARC II to load a register from memory one writes:

> LOAD ADDR, REG


**Why is the operand order different?**

I think this is preference, kinda of like at&t and intel asm. If it's better to be able to decode either the addr or the reg first, and you can't decode all at once, then there's a performance benefit, but if not, then it's personal preference.

---

## 16.
How many registers does the machine whose instruction formats are given in Fig. 5-24 have?

$2^5$, 32 registers

---

## 17.
In Fig. 5-24, bit 23 is used to distinguish the use of format 1 from format 2. No bit is provided to distinguish the use of format 3, however. How does the hardware know to use it?

This is bit 9, but, some opcodes could map to having only an offset. So for example, conditional branches only use format 3, but load and store use 2. Any other instructions that use different formats can have different opcodes (e.g. mov with format 1 = opcode 1, mov with format 2 = opcode 2)

---

## 18.
It is common in programming for a program to need to determine where a variable $X$ is with respect to the interval $A$ to $B$. If a three-address instruction were available with operands $A$, $B$, and $X$, how many condition code bits would have to be set by the instruction?

If you only care about if $X$ is in the interval or out of it, 1 bit would suffice. If you care about the total ordering of $X$ with respect to the interval, you would need to show $\lt$, $\in$, $\gt$, so 3 bits.

---

## 19.
The Pentium II has a condition code bit that keeps track of the carry out of bit 3 after an arithmetic operation. What good is it?

The carry bit is for BCD (Binary Coded Decimal) math. 

---

## 20.
The UltraSPARC II has no instruction to load a 32-bit number into a register. Instead, a sequence of two instructions, `SETHI` and `ADD`, are normally used. Is there any other way to load a 32-bit number into a register? Discuss your answer.

---

## 21.
One of your friends has just come bursting into your room at 3 A.M., out of breath, to tell you about his brilliant new idea: an instruction with two opcodes. Should you send your friend off to the patent office or back to the drawing board?

Not interesting or patentable. Two opcodes wouldn't do much for you, since you'd have to store the actual operation somewhere else, which is pretty much the same as if you had many opcodes.

---

## 22.
Tests of the form:

```c
if (n == 0) ...
if (i > j) ...
if (K < 4) ...
```

are common in programming. Devise an instruction to perform these tests efficiently.
What fields are present in your instruction?

`CMPBR R1, R2/IMM, condition, target`

We need an instruction that lets you jump to some target based on a condition (op) and takes an immediate or a register for the second field.

--- 

## 23.
For the 16-bit binary number `1001 0101 1100 0011`, show the effect of:

- a. A right shift of 4 bits with zero fill  
- b. A right shift of 4 bits with sign extension  
- c. A left shift of 4 bits  
- d. A left rotate of 4 bits  
- e. A right rotate of 4 bits  

---

## 24.
How can you clear a memory word on a machine with no `CLR` instruction?

`xor word word`, cause xoring any number with itself results in zeroes.

---

## 25.
Compute the Boolean expression:

$$
(A \text{ AND } B) \text{ OR } C
$$

For:

A = 1101 0000 1010 1101  
B = 1111 1111 0000 1111  
C = 0000 0000 0010 0000

--- 

**26.**
Devise a way to interchange two variables $A$ and $B$ without using a third variable or register.
Hint: Think about the EXCLUSIVE OR instruction.

```
x := y XOR x; 
y := x XOR y; 
x := y XOR x;
```


--- 
**27.**
On a certain computer it is possible to move a number from one register to another, shift each of them left by different amounts, and add the results in less time than a multiplication takes.

Under what condition is this instruction sequence useful for computing constant × variable?

There are a lot of strength reductions for multiplications, but if you either multiply or divide by 2, a left or right shift will be much faster than a multiplication for it.

---

**28.**

Different machines have different instruction densities (number of bytes required to perform a certain computation).
For the following Java code fragments, translate each one into:

    Pentium II assembly language

    UltraSPARC II assembly language

    JVM bytecode

Then compute how many bytes each expression requires for each machine.

Assume that i and j are local variables in memory, but otherwise make the most optimistic assumptions in all cases:

a. i = 3; 
b. i = j;  
c. i = j - 1;

a. i = 3;
Pentium II (x86 Assembly)

```
mov i, 3       ; Move immediate to memory
```

mov to memory with an immediate operand is at least 6 bytes:

1 byte opcode

1 byte ModR/M

4 bytes for address/immediate

Total: 6 bytes
UltraSPARC II (RISC Assembly)

```
set 3, %g1          ; Load immediate into register
st %g1, [i]         ; Store register to memory
```

set uses 2 instructions if constant doesn't fit in 13 bits

But 3 fits in 13 bits, so we can use:

```
mov 3, %g1          ; 4 bytes
st %g1, [i]         ; 4 bytes
```

Total: 8 bytes
JVM Bytecode

```
iconst_3     // push constant 3
istore_1     // store to local variable 1 (assuming i is at index 1)
```

    iconst_3: 1 byte
    istore_1: 1 byte

Total: 2 bytes
b. i = j;
Pentium II

```
mov eax, [j]   ; Load from memory
mov [i], eax   ; Store to memory
```

Each mov is at least 3 bytes:

    mov reg, [mem]: 3 bytes
    mov [mem], reg: 3 bytes

Total: 6 bytes
UltraSPARC II

```
ld [j], %g1    ; 4 bytes
st %g1, [i]    ; 4 bytes
```

Total: 8 bytes
JVM Bytecode

```
iload_2       // assuming j is at index 2
istore_1      // i is at index 1
```

    iload_2: 1 byte
    istore_1: 1 byte

Total: 2 bytes
c. i = j - 1;
Pentium II

```
mov eax, [j]    ; 3 bytes
dec eax         ; 1 byte
mov [i], eax    ; 3 bytes
```

Total: 7 bytes
UltraSPARC II

```
ld [j], %g1       ; 4 bytes
sub %g1, 1, %g1   ; 4 bytes
st %g1, [i]       ; 4 bytes
```

Total: 12 bytes
JVM Bytecode

```
iload_2       // j
iconst_1      // 1
isub          // j - 1
istore_1      // i
```

    iload_2: 1 byte
    iconst_1: 1 byte
    isub: 1 byte
    istore_1: 1 byte

Total: 4 bytes

--- 

29.

The loop instructions discussed in the text were for handling for loops.
Design an instruction that might be useful for handling common while loops instead.

For and while loops can be lowered to the same assembly using jumps.

However, you could support something like:

```
wloop cond_reg, loop_exit
jmp wloop_start
```

Instead of the usual:

```
cmp cond_reg, 0
je  loop_exit
jmp loop_start
```

Which saves one instruction.

--- 

**30.**

Assume that the monks in Hanoi can move 1 disk per minute (they are in no hurry to finish the job because employment opportunities for people with this particular skill are limited in Hanoi).
How long will it take them to solve the entire 64-disk problem?
Express your result in years.

600B years

--- 

31.

Why do I/O devices place the interrupt vector on the bus?
Would it be possible to store that information in a table in memory instead?

--- 

32.

A computer uses DMA to read from its disk. The disk has 64 512-byte sectors per track.
The disk rotation time is 16 msec. The bus is 16 bits wide, and bus transfers take 500 nsec each.
The average CPU instruction requires two bus cycles.

How much time is the CPU slowed down by DMA?


- **Each CPU instruction uses 2 bus cycles**  
	- So each instruction uses $2 \times 0.5 = 1, \mu s$ of bus time


Each track has:

$$64×512=32, ⁣768 bytes=32 KB64 \times 512 = 32,\!768 \text{ bytes} = 32 \text{ KB}64×512=32,768 bytes=32 KB$$


Each DMA transfer moves 2 bytes:

$$32,⁣768 2=16, ⁣384 DMA transfers\frac{32,\!768}{2} = 16,\!384 \text{ DMA transfers}232,768​=16,384 DMA transfers$$



### 🧮 Step 3: Total DMA Bus time


$$16,⁣384×0.5 μs=8, ⁣192 μs=8.192 ms16,\!384 \times 0.5\, \mu s = 8,\!192\, \mu s = 8.192 \text{ ms}16,384×0.5μs=8,192μs=8.192 ms$$

---

### 🧮 Step 4: Fraction of time DMA Occupies the Bus

Total rotation time: 16 ms  
DMA bus time: 8.192 ms

So:

$$
\begin{align}
c * {8.192}{16} = 0.512 = 51.2\%
\\
168.192​=0.512=51.2\%
\end{align}
$$

--- 
33.

Why do interrupt service routines have priorities associated with them whereas normal procedures do not have priorities?

Interrupts are asynchronous, so they have to be worked on after they are scheduled -- some interrupts are more valuable than others, so they should be driven to completion earlier (e.g. context switch timer vs mouse or keyboard input).

Procedural code normally does not let some code preempt other code, as it goes top-down, and so scheduling is less important -- it executes in a sorted order. However, with more async programming, some threads of execution can have a higher priority, so this has come into higher-level programming as well.

--- 
34.

The IA-64 architecture contains an unusually large number of registers (64).
Was the choice to have so many of them related to the use of predication?

  If so, in what way?

  If not, why are there so many?

1. There's actually more registers since the book came out, but taking the "large" number of registers: 64 are predicate based. This is to make the machine easier to generate vectorized (SIMD) code for, since branches slow down code, but predicated instructions are faster since they can rely on a bit in the predicate 64-bit registers on whether or not to execute.
2. Outside of predication, having more registers available for compilers + code makes data related programs faster, which is a benefit for most programs.

---

35.

In the text, the concept of speculative LOAD instructions is discussed.
However, there is no mention of speculative STORE instructions.

Why not?

Are they essentially the same as speculative LOAD instructions, or is there another reason not to discuss them?

I think you could have speculative store instructions, however, this would require that stores are visible to certain instructions. In database land, this would be MVCC -- every tuple requires a transaction that it is visible starting from (xmin) and stops being visible at (xmax). So, every load/store needs to interact with some manager that can tell it which physical memory cell to look at.

Speculative store instructions do currently exist. They are, however, costly, and thus special purpose instead of general purpose.

Speculative loads are easier to implement than stores because they don't mutate state -- after a read is required, it can be checked for validity before moving on, and if not, it can be discarded -- no writes pile up, just more reads.

The way stores are speculatively executed is with store buffers.

--- 

36.

When two local area networks are to be connected, a computer called a bridge is inserted between them, connected to both.
Each packet transmitted on either network causes an interrupt on the bridge, to let the bridge see if the packet has to be forwarded.

Suppose that it takes 250 μsec per packet to handle the interrupt and inspect the packet, but forwarding it, if need be, is done by DMA hardware without burdening the CPU.
If all packets are 1 KB, what is the maximum data rate on each of the networks that can be tolerated without having the bridge lose packets?

So, with 250 microseconds per packet, and needing to forward for two networks, assume that's 4 packets per millisecond, and 4000 packets per second. Divide by 2 for the packet rate for the two networks. This would be 2MB/s.

Assuming the packets come in at a constant rate and don't overflow the bridge.

--- 

37.

In Fig. 5-41, the frame pointer points to the first local variable.
What information does the program need in order to return from a procedure?

The program needs its previous instruction's location + 1 so it can move onto the next instruction after the procedure. As well, it needs to cleanup the stack, the frame pointer, and restore registers based on the calling convention.

--- 
38.
Write an assembly language subroutine to convert a signed binary integer to ASCII.

---

39.

Write an assembly language subroutine to convert an infix formula to reverse Polish notation.


Prev: [the-microarchitecture-level](the-microarchitecture-level.md)
Next: [the-operating-system](the-operating-system.md)
