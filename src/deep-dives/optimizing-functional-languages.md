# Optimizing Functional Programming Languages vs. Imperative Programming Languages

## FP Optimizations

Functional programming languages are immutable and referentially
transparent, which means compilers can be aggressive in optimizing code.
Some optimizations are:

- Common Subexpression Elimination (CSE). In a purely functional
  language, any expression yields the same result given the same inputs.
  Imagine you have an `expensive_function(X)` and your function calls
  this twice. You can replace calls to `expensive_function(X)` with its
  result. Even better, if the call is static, every call site can be
  replaced with this result as well.

- Function Inlining: Immutability means that inlining functions will not
  alter program behavior -- thus functional compilers will inline
  functions across modules to allow for extra optimizations, like
  constant folding, dead code elimination, and unboxing of values.

- Tail-Call Elimination: turning recursive calls into O(1) memory jumps.

- Lazy Evaluation Optimizations: Haskell is a lazy language, so it can
  defer computation until it's needed. Strictness analysis determines
  when expressions will be needed and evaluates them eagerly.

- Aliasing Optimizations: data is immutable, and pointers cannot alias
  mutable state. Thus, FP languages don't need to worry about alias
  analysis. This allows compilers to more easily reorder instructions or
  keep values in registers without reloading them.

- Loop fusion: If you call `filter(map(list))` in an imperative
  language, you must always do two loops over the list. The reason is
  because filter and map can mutate non-local state. In an FP language,
  with referential transparency, this can be shortened into one loop,
  and also easily vectorized.

- Memoization: Referential transparency means that results can be cached
  and reused reliably. The compiler can pick opportunities it thinks
  expressions are expensive and then cache said results.

- Garbage Collection: FP languages use GC for memory management. Because
  pointers will not be modified to point to newer objects, the GC can be
  optimized to ignore this case, which imperative languages cannot.

## Imperative Optimizations

- Low level imperative languages allow for placing data on the stack or
  the heap, and also perform escape analysis to determine if an object
  can be placed on the stack or in a register.

- In-place updates: in-place updates allow imperative programs to update
  data without a copy.

- Loop optimizations: imperative languages can more easily apply
  auto-vectorization if they can prove that there's no cross-iteration
  data dependence.

- Alias analysis with types: `restrict` and similar keywords allow the
  compiler to be laxer on alias analysis, unlocking the same
  optimizations in imperative languages.
