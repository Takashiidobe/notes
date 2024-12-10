---
title: Use Rust
date created: Sunday, December 8th 2024, 2:33:49 pm
date modified: Tuesday, December 10th 2024, 8:48:42 am
tags: [adr]
---

# Use Rust

* Status: **Accepted**
* Date: **2024-12-10** 

## Context

Rust is the main programming language I use, as it is the language I have used that meets most of my values. Stability is a core deliverable, and has been since [version 1.0 released in 2015](https://blog.rust-lang.org/2015/05/15/Rust-1.0.html).  It also allows for correctness by default, by having immutable variables by default, pattern matching, algebraic data types, and a borrow checker, which prevents many concurrency and memory safety bugs. As well, it is easy to deploy, as binaries are statically linked (no need for a VM to go along with the compiled code) and maintainable, as the compiler assists in enforcing invariants in code.

There is also no need to worry about stagnation like in C, where only backwards compatible changes can be considered, or stability at the cost of performance, as in C++. Rust allows for backwards compatible changes through the ecosystem using [editions](https://doc.rust-lang.org/edition-guide/editions/), which allows the language to evolve yet still compile old code alongside new versions of the code. In C and C++, because of ABI constraints, backwards incompatible changes are generally rejected, even in the case where performance could be improved or the language could be simplified. Because Rust has no stable ABI, it is able to optimize the layout of code, as long as it does not break its API. Even if there's an API break, that can be handled in an edition, so people who upgrade editions can opt-in to performance or correctness updates in the standard library.

Rust has a mature ecosystem with many libraries, such as regex, serde, and web libraries like axum, and an async runtime, like tokio. These are a one liner to include in a project, and greatly aid in writing code that doesn't compromise on performance, correctness, and maintainability.

## Decision Drivers

* **Stability**
* **Correctness**
* **Maintainability**
* **Portability**
* **Expressiveness**

## Considered Options

* **Rust**
* **Go**
* **C++**
* **C**

## Decision Outcome

Chosen option: **Rust**, as it best meets all of the criteria above.

### Positive Consequences

* Rust has a focus on stability, where there will never be a version 2 of the language. Go is trending towards that direction, and C++ already breaks code every 3 years by removing old language features.
- Rust is more expressive than C and Go by design, and in the case of C++, does not compromise on clarity, safety, and performance while doing so.
- Rust has first class ADTs, pattern matching, a borrow checker, and an easier portability story than C or C++. It also supports more platforms than go. 

### Negative Consequences

* The rustc compiler is another requirement on my machine to deploy code. Most machines already have a C compiler, but they tend not to have a rustc compiler. 
* The language can have churn. The ecosystem can change quite often, and crates may fall in and out of favor. It's important to exercise caution when choosing a library to depend on for the future.
- Compile times. Rust has slower compile times than even C++ in certain cases, whereas C and Go are relatively fast to compile. This impedes on iterating on code, and negatively affects velocity.

## Pros and Cons

### **Rust**

* Good, because **of its commitment to stability** 
* Good, because **it values correctness**
* Good, because **it values expressiveness**
* Good, because **it has a mature ecosystem**
* Bad, because **has slow compile times**
* Bad, because **is a complicated language**

### **Go**


* Good, because **it values simplicity**
* Good, because **has a mature ecosystem**
* Good, because **it has fast compile times**
* Bad, because **the language has less focus on correctness**

### **C++**

* Good, because **It has many features**
* Bad, because **the language is unstable**
* Bad, because **the language is complicated**
* Bad, because **the ecosystem is fragmented**
* Bad, because **the language is memory unsafe**

### **C

* Good, because **it is ubiquitous **
* Good, because **values simplicity**
* Bad, because **the language isn't expressive**
* Bad, because **the language is memory unsafe**
## Changelog

* 2024-12-10 ADR created

