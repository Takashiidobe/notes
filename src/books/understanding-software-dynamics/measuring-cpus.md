---
title: "Measuring CPUs"
---

# Measuring CPUs

Prev: [my-program-is-too-slow](my-program-is-too-slow.md)
Next: [measuring-memory](measuring-memory.md)

CPU performance is hard to measure, due to the following techniques:

- CPU and memory clocks decoupled
- Multiple memory banks
- Multiple data registers
- Multiple instructions per word
- Instruction pipelining
- Multiple execution units
- Speculative execution
- Multiple instruction issuing
- Out-of-order execution
- Cache memory
- Paged virtual memory
- Multithreading

Latency is hard to measure due to the following, as well as power
saving. Most computers nowadays are heterogeneous, with efficiency cores
and performance cores, where performance cores take more energy but have
more performance, and efficiency cores take less energy but have less
performance.

As well, CPU clocks can be dynamically slowed down to increase
efficiency, making the idea of a "cycle" hard to measure.

Thus, to measure the latency of something you have to run it quite a few
times.

The code shown in the book, when optimized, shows that there's no
latency, as the code is optimized away.

The compiler can also remove dead code, and reorder code, so you have to
be careful about benchmarking. Also, the compiled assembly isn't the end
all be all, because the actual compiled code is also compiled in RISC 86
ops.

## Exercises

2.1 What is the latency of add?

- On a superscalar processor, since many instructions can be pipelined,
  I would expect the cycle count of adds done in succession to approach
  close to 0.1 cycles, since my computer can do many more than 10 adds
  in a single cycle.

2.2 Run mystery1.cc both unoptimized -O0 and -O2, explain the
differences:

- The unoptimized version runs the code as expected, and -O2 optimizes
  it away.

2.3 Uncomment the fprintf, see what changes:

- If i uncomment the last fprintf, I assume that it can't optimize away
  the code.

2.4 Declare incr as volatile and run again:

- If declared as volatile, the optimizations stop and the code looks
  closer to as -O0.

2.5 Make your own copy of mystery1.cc and modify it to measure the
latency of cycles in a 64-bit integer add. Write down your answer.

- I assume it approaches 1 cycle since the optimizations would prevent
  parallelism and vectorization.

2.6 Experiment with the number of loop iterations. Explain why some
values do not produce meaningful results.

- Some values are too small to give a meaningful result and some values
  are too large, and thus would take too long on a server and could be
  affected by other processes.

2.7 Write down your guess for latency of integer 64 bit multiply and
divide and floating point multiply and divide.

Integer Multiply: ~15 cycles
Integer Divide: ~20 cycles

FP multiply: ~30 cycles?
FP Divide: ~40 cycles?

2.8 Now verify your guesses:

- I'm not going to use the program and I'll look at Agner Fog's
  latencies:

Integer multiply: 3-4 cycles
Integer Divide: 9-17 cycles

FP multiply: 6-7 cycles
FP Div: 15 cycles

2.9 Have your double precision drift into underflow and overflow ranges.
Point out the observed latency.

- I assume that latency turns into close to nothing because
  overflow/underflow can be handled with a single comparison.

Prev: [my-program-is-too-slow](my-program-is-too-slow.md)
Next: [measuring-memory](measuring-memory.md)
