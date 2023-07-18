---
title: "Turing machines"
---

# Turing machines

Prev: [circuits-and-finite-automata](circuits-and-finite-automata.md)
Next: [reducibility-and-gödel](reducibility-and-gödel.md)

## Previously

We discussed finite automata and circuits. Finite automata recognizes many properties of arbitrarily long input, but circuits represent any boolean function.
Circuits are limited by input size, and finite automata are limited by memory size.

## Turing Machines

How can we generalize finite automata to overcome their limitations?

Let's say we can move left and right on the tape, instead of just right. This provides no extra power, sadly. To see why, we can express going backwards on the tape with a one-way machine
that keeps track of the whole function f instead of just the state a.

The way to make the machine more powerful is to add the ability to write to the tape and halt at any time. Writing gives turing machines infinite memory, and halting allows turing machines
to not be tied to an input, like a finite automata would.

Thus, at any point, a turing machine has three questions it can ask:

1. Change state?
2. Write to the tape?
3. Move left, right, or halt?

This allows the turing machine to check for palindromes in $O(n^2)$ time, which is the best it can do, but it can now do something FSMs and circuits cannot.

## Universal Turing Machines

In Turing's paper, "On Computable Numbers", Turing proved that we can build a Turing machine *U* that simulates any other Turing machine step by step.
If a universal machine didn't exist, we'd need to build new hardware for every problem. Without this, the software industry wouldn't exist.

If a turing machine is emulating another turing machine with more states, it can emulate the other turing machine with extra state on blank sections of its tape.

## The Church-Turing Thesis

The Church-Turing thesis claims that anything we would regard as "computable" is computable by a Turing machine. With any reasonable model of computation,
like the RAM model, or cellular automata, you can translate programs back and forth between that and a Turing machine.

## Halting is a problem

Assume we have a turing machine that never halts. Can we use another turing machine to detect if that machine either never halts or halts? That's the halting problem.

One reason why we want this is we could prove or disprove Goldbach's Conjecture, which says that all even numbers 4 or greater are the sum of two primes.

One could write this program:

```
for i = 2 to infinity:
    if 2 * i is not a sum of two primes
        HALT
```

We would plug this machine into an infinite-loop detecting turing machine. If the machine halted, then we'd know the program must encounter a number for which the conjecture didn't hold. But if it never halted, the conjecture was true.

We can argue by contradiction. Let *P* be a turing machine that solves the halting problem. If *P* is given a machine *M*, *P(M)* accepts if *M(0)* halts, and rejects if *M(0)* runs forever. *M(0)* means to run *M* with only 0s on its tape.

We can then create a new machine, *Q*, which when run as *Q(M)*, then runs forever if *M(M)* halts, or halts if *M(M)* runs forever.

What happens when we give *Q* to itself? If *Q(Q)* halts, then *Q(Q)* runs forever. If *Q(Q)* runs forever, then *Q(Q)* halts. Thus, the machine *Q*'s existence is logically unsound.

Thus, with a turing machine, the halting problem is *undecidable*. It cannot be *computed* by a turing machine.

## There are multiple infinities

Cantor discovered that there are different kinds of infinity. The infinity of real numbers is greater than the infinity of integers.

There are more real numbers than there are integers. Real numbers are uncountably infinite, whereas integers are countably infinite.

To prove this, you can do it by contradiction. If real numbers and integers were the same class of infinity, there should be a unique 1 to 1 mapping between the two. We'll explain why this isn't possible.

Imagine you try to pair off every positive integer with a real number $x \in \[0, 1\]$.

But note that since real numbers are infinitely long, while we create our mapping, there can be another real number who's $n^{th}$ digit is the opposite of the $n^{th}$ digit of the $n^{th}$ number.

Note that rational numbers are countable, as they can be represented by a finite-length string, so there is a one-to-one association of integers to rational numbers.

## Infinitely many unsolvable problems

We can use this proof to prove that there are uncomputable problems.

Turing machines are a set of states and a set of transitions from each state to another state. These are both finite.

Thus, the number of Turing machines is countable. We can flatten each machine into one finite-length string that describes it, and create a 1:1 mapping to integers.

Problems can be mapped to the number of real numbers. A function that maps every input $x \in 0, 1$ to an output (0 or 1). Thus, with Cantor's proof, there are far more problems than there are Turing machines to solve them.

Prev: [circuits-and-finite-automata](circuits-and-finite-automata.md)
Next: [reducibility-and-gödel](reducibility-and-gödel.md)
