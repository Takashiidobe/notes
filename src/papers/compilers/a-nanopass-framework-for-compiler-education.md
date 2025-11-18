---
title: "A Nanopass Framework For Compiler Education"
pdf_url: "[[a-nanopass-framework-for-compiler-education.pdf]]"
---
## Notes

This paper suggests creating compilers as a set of passes which each perform a single task, primarily for an educational setting. 

The current way of teaching is called a micropass compiler, which has a single specific task which does a task over code to improve it in some way. 

The authors used this in their courses to have their students write more ambitious projects, including writing sparc assembly code and even writing a graph coloring register allocator.

However they suggest some cons with this approach too: each pass requires traversing the code once, which introduces noise. As well, grammars are written out as documentation but not enforced, which can make for problems when debugging.

With the nanopass methodology, they suggest:
1. The IR grammars are specified and enforced
2. Each pass only handles forms which transform in the end
3. IR is represented as records.

To define an intermediate language, there is a form which defines a language and its grammar:

```scheme
(define-language L0 over
	(b in boolean)
	(n in integer)
	(x in variable)
where 
	(Program Expr)
	...
)
```

Languages can also be inherited:

```scheme
(define-language L1 extends L0
over
- (b in boolean)
where
- (Expr b (if e1 e2 e3))
+ (default in Expr)
(case x (n1 e1) ... default)))
```

So a new language, L1, can be created from L0, where it removes the boolean terminal, and expr alternative, and replaces Expr if with Expr case.

Passes then take a given language and output another:

```scheme
(define-pass convert-assigned L1 -> L2
	...
)
```