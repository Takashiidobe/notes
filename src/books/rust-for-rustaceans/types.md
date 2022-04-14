---
title: "Types"
---

# Types

Prev: [foundations](foundations.md)
Next: [designing-interfaces](designing-interfaces.md)

## Types in Memory

Every Rust value has a type. Types tell you how to interpret the bits in
a location.

### Alignment

How much space does a boolean take? Surprisingly, it takes a byte.

```rs
// This costs 8 bytes, instead of 5 bytes as you might expect.
struct User {
  is_active: bool,
  age: u32,
} // std::mem::size_of::<User>() == 8;
```

This is due to alignment. On a 64-bit computer, all values must be byte
aligned, so any type must be placed in an address that is a multiple of
8 bits.

You can try to pack the struct above to take less memory, but it makes
reads must slower.

This costs 5 bytes as you might expect:

```rs
#[repr(packed(1))]
struct User {
  is_active: bool,
  age: u32,
} // std::mem::size_of::<User>() == 5;
```

If you have a struct value that is not byte-aligned, it takes two reads
instead of one to read the value, which is significantly slower. This is
why the Rust compiler automatically packs your structs to be byte
aligned.

### Layout

The Rust compiler gives few guarantees for struct alignment because it
does not export a stable ABI. We can ask the compiler to export a struct
in the way the C/C++ compiler would with `#[repr(C)]`.

```rs
#[repr(C)]
struct Foo {
  tiny: bool, // 1 byte
  normal: u32, // 4 bytes
  small: u8, // 1 byte
  long: u64, // 8 bytes
  short: u16, // 2 bytes
}
```

With `#[repr(C)]`, This would cost 8 bytes for `tiny`, `normal`, an
extra 8 bytes for `small`, then `8 bytes` for long, and `8 bytes` for short,
for a total of 32 bytes.

With `#[repr(Rust)]`, the default representation, this would cost us 16
bytes, half of `#[repr(C)]` since the compiler will reorder the items
from largest to smallest.

```rs
#[repr(Rust)]
struct Foo {
  long: u64, // 8 bytes
  normal: u32, // 4 bytes
  short: u16, // 2 bytes
  small: u8, // 1 byte
  tiny: bool, // 1 byte
}
```

You can pack a struct to be memory efficient using `#[repr(packed)]`,
which is good for sending the in-memory representation in a memory
constrained environment, like over the network.

You can also use `#[repr(align(n))]` to align to a certain byte standard
to avoid `false sharing`, which can cause performance degradations in
concurrent programs.

### Complex Types

Tuple: Represented like a struct
Array: Represented as a contiguous sequence without padding between
elements.
Union: Layout is chosen independently of each variant. Alignment is the
maximum across all the variants.
Enumeration: Same as union, but with one hidden field to store the enum
variant discriminant.

### Dynamically Sized Types and Wide Pointers

Most objects are sized by default, but some are not. For example, `dyn Iterator` and `[u8]`.

Most types are `T: Sized` by default because the compiler needs to know
types at compile time, due to this.

The way this is solved is by passing a `fat/wide pointer`, a pointer
that also contains an extra word-sized field that contains information
about the size of the dynamically sized type.

Crucially, fat pointers are sized.

## Trait and Trait Bounds

### Compilation and Dispatch

When you write a generic type over T, the compiler `monomorphizes` that
code, or generates a version of the code for each type that uses it.

This occurs for generic structs and functions.

This is called `static` dispatch, since this can be rewritten at compile
time.

Normally this is without runtime cost, but this does slow compile times
and make CPU misses more common.

The alternative is _dynamic dispatch_, which allows code to call a trait
method on a generic type without knowing what that type is.

This can be done with `&dyn trait`, which makes it so the caller must
provide a pointer to a chunk of memory that the method will call.

We have to use a reference to the trait because we no longer know its
size.

Dynamic dispatch looks like this:

```rs
impl String {
  pub fn contains(&self, p: &dyn Pattern) -> bool {
    p.is_contained_in(&*self)
  }
}
```

The combination of a type that implements a trait and its vtable is a
_trait object_.

Dynamic dispatch improves compile times, but at the cost of
optimizations that the compiler would otherwise be able to do.

Generally for libraries, static dispatch is preferred and dynamic
dispatch is preferred for binaries.

## Generic Traits

Traits can be generic in two ways: with generic type parameters like
`trait Foo<T>` or associated types like `trait Foo { type Bar; }`.

Use an associated type if you expect only one implementation of the
trait for a given type, otherwise, a generic type parameter.

### Coherence and the Orphan Rule

Rust needs strict rules so there is only one correct choice for
implementation of a method on a trait.

Rust also needs to allow different crates to implement traits, and also
for the standard library.

The `orphan rules` prevent you from writing an `impl` on a trait if the
trait and type are defined in a different crate.

Prev: [foundations](foundations.md)
Next: [designing-interfaces](designing-interfaces.md)
