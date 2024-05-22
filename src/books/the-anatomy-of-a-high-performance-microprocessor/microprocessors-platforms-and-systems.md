---
title: "Microprocessors, Platforms and Systems"
---

# Microprocessors, Platforms and Systems

Next: [a-microarchitecture-case-study](a-microarchitecture-case-study.md)


When designing a Microprocessor, specific workloads and benchmarks are
extremely important to design for. Backwards compatibility too - even
though the 80286 instructions extended addressable memory from 1MB to
16MB, it was not commonly used. It failed to be compatible with the
8086, and was supplanted by the 80386's emulation of 8086 code. Thus,
every chip must support these instructions to be "x86_64" compatible,
even though they are rarely used.

Thus, a well designed ISA has the following sets of instructions

- A core of frequently used instructions
- Some features extending or correcting limitations in the original
  design
- Some instructions that are there for backwards compatibility.

There are also many decisions to make at the chip level:

1. Many parallel pipelines (shallow) or fewer deeper pipelines?
2. Instruction decodes/clock (speed)
3. What are the functional units? How are they pipelined?
4. How will functions be assigned to a pipeline?
5. What caching should be employed, and where?

Testing is extremely important -- there can be thousands of bugs at the
chip level, and verification is extremely important since users may
return chips that aren't fully spec compliant.


Next: [a-microarchitecture-case-study](a-microarchitecture-case-study.md)
