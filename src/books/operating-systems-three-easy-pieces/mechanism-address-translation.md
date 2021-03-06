---
title: mechanism-address-translation
---

# Mechanism: Address Translation

Prev:
[interlude-memory-api](interlude-memory-api.md)
Next: [segmentation](segmentation.md)

In virtualizing memory, we need efficiency and abstraction. To do so,
we'll do address translation, where each memory access is transformed
from the virtual address to a physical one.

The hardware cannot do this alone, hence it is the OS' job to do so.

This creates the illusion that each program has its own private memory,
even though the reality is that many programs are running on the CPU at
the same time, using the same memory.

## Assumptions

1. assume that the user's address space is placed contiguously in memory 
2. virtual memory is less than physical memory
3. each address space is the exact same 

## An Example

Take this code:

```c
int x = 3000; // thanks, Perry.
x = x + 3; // line of code we are interested in
```

```asm 
128: movl 0x0(%ebx), %eax ;load 0+ebx into eax
132: addl $0x03, %eax ;add 3 to eax register
135: movl %eax, 0x0(%ebx) ;store eax back to mem
```

We want to virtualize this process by relocating its process in memory
in a way that is transparent to the process. 

## Static (Software-based) Relocation

We could have software-based protection, where if an instruction was
issued, the assembly would be rewritten to move the allocation to the
right location (translating address 1000 to 4000, for example). However,
this doesn't allow for protection (since processes can index into other
processes memory without hardware faults).

## Dynamic (Hardware-based) Relocation

To understand hardware-based address translation, we'll use dynamic
relocation, where each CPU has two registers, the base and the bounds
(the limit). 

Each process believes it has a chunk of memory from 0 - 32kB (for
example). The OS then decides where to set the base register (maybe
something like 64KB) and then sets the limit (32KB). When any memory
reference is generated by the process, it is translated to the virtual
address.

If we index out of bounds (i.e. try to grab something at the 33rd KB,
then we will get a segmentation fault, where this is outside the limit
of the process, and will get killed).

## Hardware Support: A Summary 

We need a few things for hardware support:

The OS runs in kernel mode, where it has access to the entire machine.
Applications run in user mode, where they are limited in what they can
access.

The hardware provides the base and bounds registers, where each CPU has
an additional pair of registers as part of the MMU.

The hardware must be able to raise exceptions and the OS must be able to
handle them as well.

## Operating System Issues 

The OS needs to be able to do the following:

1. Memory management 
  - Allocating memory for new processes
  - Reclaim memory from terminated processes 
  - Manage memory via a free list 
2. Base/bounds management
  - Set base/bounds pairs for each process and be able to load/store
    them independently.
3. Exception handling
  - OS must handle exceptions 
  - And terminate processes that misbehave.

Prev:
[interlude-memory-api](interlude-memory-api.md)
Next: [segmentation](segmentation.md)

