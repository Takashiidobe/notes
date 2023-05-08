---
title: "Assembly Language & Computer Architecture"
---

# Assembly Language & Computer Architecture

Prev: [bit-hacks](bit-hacks.md)
Next: [c-to-assembly](c-to-assembly.md)

There are 4 stages to turn source code into a binary:

1. Preprocessing (`clang -E main.i)`). This expands macros.
2. Compiling (`clang -S main.s)`). This turns code into assembly.
3. Assembling (`clang -c main.o`). This turns code into objects.
4. Linking: (`ld main`). This creates the main executable.

- Machine code with debug symbols (`-g`) allows you to produce a disassembly of the code.

**Why look at assembly?**

- The compiler made an error - sometimes bugs show up only at higher optimization levels.
- reverse engineering.

Your computer's instruction set architecture (ISA) has four main concepts:

- Registers
- Instructions
- Data Types
- Memory Addressing


Prev: [bit-hacks](bit-hacks.md)
Next: [c-to-assembly](c-to-assembly.md)
