---
title: "Go To Statement Considered Harmful"
pdf_url: "[[go-to-statement-considered-harmful.pdf]]"
---
In this classic Dijkstra note, he says that `goto` makes programs difficult to reason about and prove correct. Thus, programmers should used structured control constructs.

## Use Structured Programming Constructs

His claim is that constructs like `if`, `while`, `for`, and recursion rather than arbitrary jumps make for easier to understand programs. `goto` can be used in exceptional cases. Note that `goto` in C is not the same as `goto` from this paper; you can jump anywhere with `goto` in unstructured languages, but in `C` you can only jump to the same function, which is much easier to reason about.

## Reasoning about Programs

- Dijkstra models program as a kind of graph that holds state, where variables can come from different locations and end up in a specific state.
- A proper understanding of a program comes in from seeing how variables change state.
- Structured control flow clears up state transitions -- however, arbitrary jumps disrupt these state transitions.

## Complexity of Jumps

- A goto can transfer to any labeled statement.
- You must remember all possible jumps and note it can come from anywhere.
- Structured constructs **restrict** how control can move. It **reduces** the number of entry points.

## Proof and Correctness

- Programs should be verifiable according to Dijkstra. Structured control allows for reasoning about correctness by proving invariants, pre and post conditions, and composing these to discuss correctness of a program.
- `goto` ruins this by being able to arbitrarily jump in and out of locations.

## Alternative Constructs

- most uses of `goto` fall into 3 categories:

1. Loops: use `while`, `for`, `repeat until` or other constructs.
2. Conditionals: use `if`, `else`, `cond`, `switch`, or `match`.
3. Exiting from the middle: `break`, `continue`, `exceptions`, `return`.

## Human limitations

- We have limited cognitive ability to understand complicated programs.
- Structured programming reduces complexity to make it easier to understand programs.
- We can create programs with stepwise refinement -- start from a specification and implement parts, and then refine it into detailed structured fragments.

## Legacy

Most high-level languages don't have `goto` today. `C` and `C++` have limited `goto`, and although they have `longjmp` and `setjmp`, those are rarely used. Signals are also considered hard to use in C.