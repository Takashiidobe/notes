---
title: "A Brief History Of Just In Time"
pdf_url: "[[a-brief-history-of-just-in-time.pdf]]"
---
## Notes

This paper talks history for JIT systems + a classification for JIT systems.

JIT compilers do transformations to a program after a program starts, unlike the traditional compiler, which does its transformations before a program runs. This is to:

- Improve speed
- Lower memory usage
- Access runtime information unavailable at compile time.

## History

- Lisp, LC2, APL, Smalltalk, Self, etc.

The main idea is that frequently executed parts are compiled natively, and cold code is interpreted, and some code can be thrown out when memory is tight.

Oberon supported shipping an AST like high-level representation, where code was generated at load time, allowing for continuous optimization.

## Classification

Aycock proposes three axes for JIT systems:

1. Invocation
	- Explicit: user must request compilation at runtime
	- Implicit: compilation triggered automatically (more common)
2. Executability
	- monoexecutable: system can only run native code
	- Poly-executable: can execute the source and compiled form, making decisions of when to JIT
3. Concurrency:
	- Non-concurrent: program pauses to compile
	- Concurrent: compiler runs in a separate thread and optimizes code while program runs


Currently, implicit invocation, polyexecutability, and concurrency is the way forward (in 2025, I would say this is definitely the case)

## Tools for JITs

There are some toolkits which help in the following:

1. Binary code generation
2. Cache coherence
3. Execution constraints
