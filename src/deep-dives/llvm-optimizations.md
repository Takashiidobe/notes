# LLVM Optimizations

LLVM optimizations can be split into three types:

1. Analysis: for computing information for debugging or use by
   transformation passes
2. Transformation: to mutate the program and optimize it
3. Utility passes: for debugging or testing a particular program

## Analysis Passes

Analysis passes can be grouped into:

1. Function analysis - dominator and data flow calculations
2. Module analysis - finding module boundaries and intra-module deps
3. Loop analysis - calculating loop nesting and loop invariant code
   motion metadata
4. Memory analysis - alias and escape analysis
5. Target specific analysis - optimizations for specific archs
6. Resource usage analysis - checking usage of registers, the stack, etc

## Transformation passes

1. instruction combining - simplifies and combines similar instructions
2. loop invariant code motion - moves computations in a loop that are
   invariant outside the loop
3. global value numbering - identifies and eliminates redundant
   computations across a program
4. dead code elimination - removes code that does not affect behavior of
   a program
5. loop unrolling - optimizing loops
6. vectorization - turning data independent loops into vectorized loops
7. mem2reg - promote stack references to register references
8. constant propagation - merging constant values and replacing values
   with constants where possible
