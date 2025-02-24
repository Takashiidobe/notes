---
title: The Go Garbage Collector
date created: Monday, February 24th 2025, 7:27:58 am
date modified: Monday, February 24th 2025, 7:37:50 am
---

[A Guide to the Go Garbage Collector](https://tip.golang.org/doc/gc-guide)
[The Journey of Go's Garbage Collector](https://go.dev/blog/ismmkeynote)

The Go Garbage collector is a non-moving (non-copying) concurrent read barrier free GC.

Go is unique because it has statically compiled AOT binaries (so the GC must fit in the binary), and many goroutines can run at any given time (many thousands). Thus, garbage collection must handle this concurrent environment. 

Go also is value-oriented, unlike JVM languages, which tend to be reference-oriented. Thus, Go can face less GC pressure, since most locals are handled by the runtime on the stack, which is much faster.

The Go GC also only offers two knobs for tuning, compared to most other languages where there are quite a lot.

Most of the key optimizations are around escape analysis, where the compiler figures out the maximum time a variable can live for. If it "escapes" its current scope, it is placed on the heap. If it doesn't, it can be placed on the stack. However, code that might print out a simple type will escape the stack, because `fmt.Print` is implemented using interfaces to print different types. This wouldn't be the case with generics or C style printf.