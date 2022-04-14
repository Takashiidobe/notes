---
title: "Types"
---

# Types

Prev: [introduction](introduction.md)
Next: [concepts](concepts.md)

## Item 1: Use the type system to express your data structures

```rs
let x: i32 = 42;
let y: i16 = x;
```

You can't put a larger integer into a smaller one:

```rs
error[E0308]: mismatched types
  --> use-types/src/main.rs:14:22
   |
14 |         let y: i16 = x;
   |                ---   ^ expected `i16`, found `i32`
   |                |
   |                expected due to this
   |
help: you can convert an `i32` to an `i16` and panic if the converted value doesn't fit
   |
14 |         let y: i16 = x.try_into().unwrap();
   |                       ++++++++++++++++++++
```

Rust also doesn't allow things that appear "safe", like putting an i32
in an i64:

```rs
let x = 42i32; // Integer literal with type suffix
let y: i64 = x;
```

Unlike in C, a char is a 4-byte type. You can convert chars to u32s just
fine, but not the other way around (not all u32s are valid chars), so
you have functions that require error handling:

`char::from_u32`
`char::from_u32_unchecked`

You can also use the newtype idiom to wrap a type:

```rs
type side = bool;

fn print(sides: side);
```

Enums can also encode data, which makes them extremely powerful.

To allow for values that can be null, use `Option<T>`, and for functions
that can fail, use `Result<T, E>`.

## Item 2: Use the type system to express common behavior

Function pointers can be used in Rust:

```rs
fn sum(x: i32, y: i32) -> i32 {
    x + y
}
// Function pointer. Needs a type.
let op: fn(i32, i32) -> i32 = sum;
```

### Closures

But they're limiting: in exchange, Rust offers three closure traits:

- FnOnce (a closure that can be called once, moves from env to closure)
- FnMut (a closure that can be called repeatedly, borrows mutably from
  env)
- Fn (a closure that can be called repeatedly, borrows immutably from
  env).

When writing code that accepts closures, **use the most general Fn trait
that works**.

As well, **prefer Fn trait bounds to bare function pointers**.

And **prefer accepting trait types to concrete types** if future
flexibility is anticipated.

```rs
fn mean(v: &vec<u8>); // accepts vector
fn mean(v: &[u8]); // accepts slice and vector
fn mean<T: Iterator<Item = T>>(iter: T); // accept any iterable
```

### Marker Traits

If you want to encode a constraint into the type system but the type
system can't check it, use a **marker trait**.

A marker trait has no methods, but requires the implementor to implement
it.

```rs
pub trait Sort {
    /// Re-arrange contents into sorted order.
    fn sort(&mut self);
}

/// Marker trait to indicate that a [`Sortable`] sort stably.
pub trait StableSort: Sort {}
```

As well, you'll encounter generic code that has lots of requirements:

```rs
pub fn debug_sorted<T>(mut collection: T)
where
    T: Sort + IntoIterator,
    T::Item: Debug,
{
    // Next line requires `T: Sort` trait bound.
    collection.sort();
    // Next line requires `T: IntoIterator` trait bound.
    for item in collection {
        // Next line requires `T::Item : Debug` trait bound
        println!("{:?}", item);
    }
}
```

You can also create a **trait object**, which requires interacting
through the concrete type through a pointer (either `&dyn Trait` or
`Box<dyn Trait>`).

## Item 3: Avoid matching on Option and Result

Prev: [introduction](introduction.md)
Next: [concepts](concepts.md)
