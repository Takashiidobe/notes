---
title: the-abstraction-address-spaces
---
# The Abstraction: Address Spaces

Prev: [[22-a-dialogue-on-memory-virtualization]]
Next: [[24-interlude-memory-api]]





## Early Systems

Early on, the OS didn't provide much other than library functions for
allocating memory.

## Multiprogramming and Time Sharing

Afterwards, OSes provided more functionality like time sharing, where
multiple processes could share work, especially during slow jobs like
I/O. Soon afterwards, time sharing systems were born, because the idea
of interactivity became more important, as many users could be using the
same machine.

This also gave birth to the idea of protection, where processes
shouldn't be able to read each others memory. 

## The Address Space 

We need an abstraction to manage data, and so, the idea of an address 
space was born, which can be visualized like this:

Code
Stack
  |
  v 
  ^
  |
Heap

This allows every process to seem like it owns all of virtual memory,
but in reality, when it makes a call to address 0, it is forwarded to
the actual address allocated for its process.

## Goals 

Thus, we decide to virtualize memory. However, we do so with these
goals:

1. Transparency: Processes shouldn't need to know about virtual memory.
2. Efficiency: The OS should make this process cheap.
3. Protection: The OS should protect processes from one another.

Prev: [[22-a-dialogue-on-memory-virtualization]]
Next: [[24-interlude-memory-api]]
