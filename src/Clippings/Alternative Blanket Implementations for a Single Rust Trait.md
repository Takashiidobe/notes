---
title: What Is a Blanket Implementation?
source: "https://www.greyblake.com/blog/alternative-blanket-implementations-for-single-rust-trait/"
author:
  - "[[Serhii Potapov]]"
published:
created: 2025-07-06
description: "A blog about software development."
tags: ["clippings"]
date created: Sunday, July 6th 2025, 3:43:47 pm
date modified: Sunday, July 6th 2025, 3:43:57 pm
---

Serhii Potapov July 01, 2025 

Rust's trait system is famously powerful - and famously strict about avoiding ambiguity.

One such rule is that **you can't have multiple blanket implementations of the same trait** that *could potentially* apply to the same type.

# What Is a Blanket Implementation?

A **blanket implementation** is a trait implementation that applies to *any* type meeting certain constraints, typically via generics.

A classic example from the standard library is how [`From`](https://doc.rust-lang.org/std/convert/trait.From.html) and [`Into`](https://doc.rust-lang.org/std/convert/trait.Into.html) work together:

```rust
impl<T, U> Into<U> for T
where
    U: From<T>,
{
    fn into(self) -> U {
        U::from(self)
    }
}
```

Thanks to this, when you implement `From<T>` for `U`, you automatically get `Into<U>` for `T`. Very ergonomic!

# The Restriction

However, Rust enforces a key rule: **no two blanket implementations may overlap** - even *in theory*. Consider:

```rust
impl<T: TraitA> MyTrait for T { ... }
impl<T: TraitB> MyTrait for T { ... }
```

Even if no type currently implements both `TraitA` and `TraitB`, the compiler will reject this. The reason? Some type *might* satisfy both in the future, and that would make the implementation ambiguous.

# A Real-World Problem

While working on [Joydb](https://github.com/greyblake/joydb), I ran into this exact problem.

I have an [`Adapter`](https://github.com/greyblake/joydb/blob/2aea9e11b1bc96e108e6c4478e599aaa587ffa8c/joydb/src/adapters/mod.rs#L50-L67) trait responsible for persisting data.

In practice, there are two common ways to implement it:

- A **unified adapter** that stores all data in a single file (e.g., JSON). In Joydb, this is [`UnifiedAdapter`](https://github.com/greyblake/joydb/blob/2aea9e11b1bc96e108e6c4478e599aaa587ffa8c/joydb/src/adapters/mod.rs#L107-L117).
- A **partitioned adapter** that stores each relation in a separate file (e.g., one CSV per relation), called [`PartitionedAdapter`](https://github.com/greyblake/joydb/blob/2aea9e11b1bc96e108e6c4478e599aaa587ffa8c/joydb/src/adapters/mod.rs#L119-L136).

Ideally, users would only need to implement one of those and get the `Adapter` trait "for free".

But Rust won't let me define two conflicting blanket implementations. So... is there a workaround? 🤔

# The Trait Definitions in Joydb

Here are the relevant traits in Joydb:

```rust
pub trait Adapter {
    fn write_state<S: State>(&self, state: &S) -> Result<(), JoydbError>;
    fn load_state<S: State>(&self) -> Result<S, JoydbError>;
}
```
```rust
pub trait UnifiedAdapter {
    fn write_state<S: State>(&self, state: &S) -> Result<(), JoydbError>;
    fn load_state<S: State>(&self) -> Result<S, JoydbError>;
}
```
```rust
pub trait PartitionedAdapter {
    fn write_relation<M: Model>(&self, relation: &Relation<M>) -> Result<(), JoydbError>;
    fn load_state<S: State>(&self) -> Result<S, JoydbError>;
    fn load_relation<M: Model>(&self) -> Result<Relation<M>, JoydbError>;
}
```

So the question becomes: **how can I let someone implement either `UnifiedAdapter` or `PartitionedAdapter`, and then get `Adapter` automatically?**

# The Workaround: Associated Type + Marker Structs

I discovered a solution in [this Rust forum post](https://users.rust-lang.org/t/two-blanket-implementations-for-different-classes-of-objects/100173/4), and I believe it deserves more visibility.

The key idea is to use:

1. **Marker structs** like `Unified<T>` and `Partitioned<T>` to wrap adapter types.
2. A helper trait, `BlanketAdapter`, implemented for each marker type.
3. An **associated type** in the `Adapter` trait to delegate behavior.

## Step 1: Marker Structs

```rust
use std::marker::PhantomData;

pub struct Unified<A: UnifiedAdapter>(PhantomData<A>);
pub struct Partitioned<A: PartitionedAdapter>(PhantomData<A>);
```

These zero-sized types are used solely for type-level dispatch.

---

## Step 2: The BlanketAdapter Trait

```rust
trait BlanketAdapter {
    type AdapterType;
    fn write_state<S: State>(adapter: &Self::AdapterType, state: &S) -> Result<(), JoydbError>;
    fn load_state<S: State>(adapter: &Self::AdapterType) -> Result<S, JoydbError>;
}
```

And the implementations:

```rust
impl<A: UnifiedAdapter> BlanketAdapter for Unified<A> {
    type AdapterType = A;

    fn write_state<S: State>(adapter: &A, state: &S) -> Result<(), JoydbError> {
        adapter.write_state(state)
    }

    fn load_state<S: State>(adapter: &A) -> Result<S, JoydbError> {
        adapter.load_state()
    }
}

impl<A: PartitionedAdapter> BlanketAdapter for Partitioned<A> {
    type AdapterType = A;

    fn write_state<S: State>(adapter: &A, state: &S) -> Result<(), JoydbError> {
        S::write_with_partitioned_adapter(state, adapter)
    }

    fn load_state<S: State>(adapter: &A) -> Result<S, JoydbError> {
        adapter.load_state()
    }
}
```

Now we have *non-conflicting blanket impls* because they apply to **different types** (`Unified<A>` vs. `Partitioned<A>`).

---

## Step 3: The Adapter Trait with Associated Type

```rust
pub trait Adapter: Send + 'static {
    type Target: BlanketAdapter<AdapterType = Self>;

    fn write_state<S: State>(&self, state: &S) -> Result<(), JoydbError> {
        <Self::Target as BlanketAdapter>::write_state(self, state)
    }

    fn load_state<S: State>(&self) -> Result<S, JoydbError> {
        <Self::Target as BlanketAdapter>::load_state(self)
    }
}
```

The key piece: the associated type `Target` tells `Adapter` whether to delegate to `Unified<Self>` or `Partitioned<Self>`.

---

# Usage Example

Let's say we need to implement a `JsonAdapter` that writes everything to a single file. It can be implemented as a `UnifiedAdapter`:

```rust
pub struct JsonAdapter { ... }

impl UnifiedAdapter for JsonAdapter {
    fn write_state<S: State>(&self, state: &S) -> Result<(), JoydbError> {
        // write entire state to JSON

    }

    fn load_state<S: State>(&self) -> Result<S, JoydbError> {
        // load state from JSON

    }
}

impl Adapter for JsonAdapter {
    type Target = Unified<Self>;
}
```

No code duplication. No conflicts. The only overhead is 3 extra lines to link things together

# Final Thoughts

This pattern - using **marker types + associated types** - gives you the flexibility of *alternative blanket implementations* while staying within Rust's coherence rules.

It's especially useful when you want to support mutually exclusive behaviors under a unified interface, without compromising on ergonomics.

# Links

- [Dicussion of this article on Reddit](https://www.reddit.com/r/rust/comments/1lovjej/alternative_blanket_implementations_for_a_single/)
- [Rustcast #6 – Traits `From` and `Into` in Rust](https://www.youtube.com/watch?v=vH5xXr81a2Y)
- [Rust Users Forum: Two Blanket Implementations for Different Classes of Objects](https://users.rust-lang.org/t/two-blanket-implementations-for-different-classes-of-objects/100173/4)
- [Joydb on GitHub](https://github.com/greyblake/joydb/)
- [Phantom Types in Rust (Blog)](https://www.greyblake.com/blog/phantom-types-in-rust/)

# Psss! Are You Looking for a Passionate Rust Dev?

My friend is looking for a job in Berlin or remote. Reach out to [**this guy**](https://www.linkedin.com/in/zekefast/).

**[Back to top](https://www.greyblake.com/blog/alternative-blanket-implementations-for-single-rust-trait/#)**