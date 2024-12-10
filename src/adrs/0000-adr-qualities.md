---
title: Qualities of an Architecture Decision Record
date created: Sunday, December 8th 2024, 2:33:49 pm
date modified: Monday, December 9th 2024, 9:46:01 pm
tags: [adr, meta]
---

# Qualities of an Architecture Decision Record
* Status: **Accepted** 
* Stakeholders: **list everyone involved in the decision** 
* Date: **2024-12-09** 

## Context

ADR stands for Architecture Decision Record, which records a decision made to address a requirement at hand. This can include technological choices (which technologies are preferred to solve a problem), philosophical choices (which values should be valued over others), practice and strategies (high level guidance on guiding principles) just to name a few.

This ADR discusses the qualities that I value when assessing technological choices, as well as the practices I prefer, with some context on why I prefer them.

In software, I prefer these values in order:

1. Stability
2. Correctness
3. Maintainability
4. Portability
5. Expressiveness 

### Stability

Stability is the most important value for me. I strongly prefer using tools with strong stability guarantees. In software, that means libraries that don't change often, or employ a strategy that makes migration with breaking changes as easy as possible.

Two examples of software which have this guarantee are Linux (quoting Linus Torvalds):

[Email](https://lkml.org/lkml/2012/12/23/75)

> If a change results in user programs breaking, it's a bug in the kernel. We never EVER blame the user programs. 

And Rust:

[Stability as a Deliverable](https://blog.rust-lang.org/2014/10/30/Stability.html)

> To put it simply, our responsibility is to ensure that you never dread upgrading Rust. If your code compiles on Rust stable 1.0, it should compile with Rust stable 1.x with a minimum of hassle.

Rust goes even further and allows for ecosystem changes with its split of stable/nightly code, as well as editions, which allow changes to the stable language that are opt-in, without breaking the ecosystem:

[What are Editions](https://doc.rust-lang.org/edition-guide/editions/)

> Rust uses **editions** to solve this problem. When there are backwards-incompatible changes, they are pushed into the next edition. Since editions are opt-in, existing crates won't use the changes unless they explicitly migrate into the new edition. For example, the latest version of Rust doesn't treat `async` as a keyword unless edition 2018 or later is chosen.

### Correctness

Any program should solve a problem it sets out to solve with minimal errors. This is important because a program that can solve a problem on only certain inputs can be far worse than not running a program at all.

Take for example, C or C++, which are memory unsafe languages. It is fairly straightforward to create a bug using code where it's possible to read privileged data or crash a computer, rendering it useless. These languages are by construction extremely unsafe, and as such, verifying correctness in these languages are very difficult.

Many programming languages use garbage collection, which renders these techniques impossible, and as such, those languages have less surface area for vulnerabilities.

This also extends to libraries -- libraries should be misuse resistant, and handle incorrect inputs without causing security vulnerabilities.

An example of a library that values correctness is [libsodium](https://libsodium.gitbook.io/doc/internals#security-first), a cryptography library. Libsodium has APIs which are easier to use than similar cryptography libraries and does extra checks while running to prevent security vulnerabilities.

> When a balance is required, extra safety measures have a higher priority than speed. Examples include:
> - Sensitive data is wiped from memory when the cost remains reasonable compared to the cost of the actual computations.
> - Signatures use different code paths for verification to mitigate fault attacks and check for small order nonces.
> - X25519 checks for weak public keys.
> - Heap memory allocations ensure that pages are not swapped and cannot be shared with other processes.
> - The code is optimized for clarity, not for the number of lines of code. Except for trivial inlined functions (e.g. helpers for unaligned memory access), implementations are self-contained. 
> - The default compiler flags use a conservative optimization level, with extra code to check for stack overflows and some potentially dangerous optimizations disabled. The `--enable-opt` switch remains available for more aggressive optimizations.
> - A complete, safe, and consistent API is favored over compact code. Redundancy of trivial functions is acceptable to improve clarity and prevent potential bugs in applications. For example, every operation gets a dedicated `_keygen()` function.
> - The default PRG doesn’t implement something complicated and potentially insecure in userland to save CPU cycles. It is fast enough for most applications while being guaranteed to be thread-safe and fork-safe in all cases. If thread safety is not required, a faster, simple, and provably secure userland implementation is provided.
> - The code includes many internal consistency checks and will defensively `abort()` if something unusual is detected. This requires a few extra checks but is useful for spotting internal and application-specific bugs that tests don’t catch.

### Maintainability

Maintainability is the ease at which a program can be modified. This allows somebody to extend software, fix its bugs, or add new features. 

Software which is maintainable can be used for longer, whereas unmaintainable software may require a rewrite in the long term, or require multiple breaking changes, which can make interfacing with the software difficult.

Software should also come with a set of tests that grant developers confidence in making changes, as tests are a specification for the behavior of a program -- if there aren't any tests, the only specification lies in the programming language itself, which can be weak, unless using a proof language.

One example can be multics vs unix. By making a simpler operating system, unix was more maintainable than multics, which led to its success in the future.
### Portability

Portability means that software can run on many different versions of hardware. Linux now is a good example of this -- it can run on [business cards](https://www.thirtythreeforty.net/posts/2019/12/my-business-card-runs-linux/): 

> All this is accomplished on a very small 8MB flash chip. The bootloader fits in 256KB, the kernel is 1.6MB, and the whole root filesystem is 2.4MB.

Or mobile phones, tablets, laptops, desktops, and supercomputers. It has great driver support these days, and it can be compiled to opt-in to many features that can enhance its performance and functionality.

For programming languages, rust supports 262 targets as of rust 1.83, including many esoteric ones. Go supports 45 or so, and VM languages might support fewer.
### Expressiveness

Expressiveness is the ease in which one can write code that's easy to understand for human readers. There are many ideas in programming that allow the writer to express complicated ideas in a simple to use format.

Some basic ideas are functions, for loops, while loops, and if conditionals, which are all implemented as jumps in assembly, but allow for a more concise representation in written language. This has perks for machines as well, as these can be optimized, either through inlining, dead code elimination, and reordering of code.

Other ideas include algebraic data types, non-nullable types, and pattern matching, which can all allow a programmer to pack more information in fewer keystrokes while still maintaining readability.

A language should have a focused set of features that make it easy to express complicated ideas without requiring the programmer to go through much ceremony to express said ideas.
## Links

* [Bryan Cantrill's Presentation on Rust's Values](https://www.slideshare.net/bcantrill/platform-values-rust-and-the-implications-for-system-software)

## Changelog

* ADR created 2024-12-09

