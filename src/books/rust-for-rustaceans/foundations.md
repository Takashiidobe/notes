---
title: "Foundations"
---

# Foundations

Next: [types](types.md)

## Talking about Memory

A variable constitutes of a type and a value.
The value is stored in a `place`, any location that can hold a value.
A pointer is a value that holds the address to a region of memory. It
`points` to a place.

```rs
let x = 42; // a value
let y = 43; // a value
let var1 = &x; // var1 refers to the same immutable reference as x;
let mut var2 = &x; // var2 is a mutable reference to x
var2 = &y; // var2 is now a mutable reference to y.
```

Note that `var1` and `var2` hold independent copies of `var1` and
`var2`.

This is useful for strings like this:

```rs
let string = "Hello world";
```

The actual value of the variable is a pointer to the first character in
the string. The string is stored elsewhere.

## Variables in Depth

We can look at variables at a high-level and a low-level. A High-level
view is more useful for thinking about lifetimes and borrows, but
low-level models are good for reasoning about unsafe code and raw
pointers.

### High-Level

In a high-level model, you can think of flows, where data flows from one
variable to another. A variable can be moved if it holds a legal value,
if it is not initialized or contains an illegal value, it cannot be
moved. Flows can fork and merge, but there are other rules, like there
can only be one flow with mutable access to a value. Nor can there be
any borrow while there is no flow that owns the value.

```rs
let mut x;
// this access would be illegal, nowhere to draw the flow from:
// assert_eq!(x, 42);
x = 42;
// this is okay, can draw a flow from the value assigned above:
let y = &x;
// this establishes a second, mutable flow from x:
x = 43;
// this continues the flow from y, which in turn draws from x.
// but that flow conflicts with the assignment to x!
assert_eq!(*y, 42);
```

If a new variable is declared with the same name as a previous one, they
are considered distinct variables. This is called _shadowing_. The two
variables coexist, but the shadowed variable becomes unreachable.

### Low-level Model

Variables name memory locations that may or may not hold legal values.
When a variable is assigned to, its value slot is filled and the
previous value is dropped before being replaced by its new value.

References do not change when you assign to the backing variable.

## Memory Regions

### The Stack

The stack is a segment of memory that your program uses to hold data for
function calls.

Each time a function is called, a chunk of memory called a `frame` is
allocated at the top of the stack. Close to the bottom is where the
`main` function is.

When a function returns, its stack frame is reclaimed.

Since stack frames disappear, any value passed to a function must last
as long as the function does, otherwise values would disappear.

### The Heap

The heap is a pool of memory that isn't tied to the current call stack
of the program. Values in Heap Memory live until they are explicitly
deallocated.

This is useful for values that need to live longer than its current
function, or to share a value with threads without stack frames.

The heap allows you to explicitly allocate contiguous segments of
memory, and returns a pointer to the start of the segment in memory when
it starts.

Since Heap memory lasts until `freed`, its lifetime is unconstrained.

In Rust, the mechanism for interacting with the heap is `Box::new(value)`,
which returns a pointer that points to that value on the heap.

You may want to `leak` memory, to cast a heap allocated type to a
`'static` type. You can do this with `Box::leak`.

### Static Memory

Static memory is a catch-all term for several regions in a binary, like
string data, read-only data, and function labels. These symbols last
forever, hence `static`.

`'static` occurs as a type trait frequently, for example, for thread
functions, since a function must live at least as long as the thread
does.

Note: `const` is like `constexpr` in C++, it means anything that can be
computed at compile time.

## Ownership

All values in Rust must have a single owner. That means that one
location is responsible for deallocating each value.

For normal types, if a variable is reassigned, it is dropped at its old
location and moved to its new one.

Some primitive types are copy, which means the assignment operator
copies it over to its new location, so there are now two copies of the
data.

Here's an example:

```rs
let x1 = 42; // 42 is Copy
let y1 = Box::new(84); // y1 is Move
{ // starts a new scope
  let z = (x1, y1); // z goes out of scope, and is dropped;
  // it in turn drops the values from x1 and y1
}
// x1's value is Copy, so it was not moved into z
let x2 = x1;
// y1's value is not Copy, so it was moved into z
// let y2 = y1; Compiler error
```

### Drop Order

Rust automatically drops values when they go out of scope. Variables are
dropped in reverse order, and nested values are dropped in source-code
order.

For variables this makes sense:

```rs
let s = "hi"; // then this
let mut h = HashMap::new(); // this gets dropped first
h.insert(&s, 1);
```

Because this would result in UB:

```rs
let s = "hi"; // 1. Delete this:
let mut h = HashMap::new(); // 2. `h` holds a reference to deleted memory.
h.insert(&s, 1);
```

For Nested Types, like tuples, arrays, and structs, this isn't true:

```rs
let a = vec![1,2,3]; // First 1 is dropped, then 2, then 3.
```

## Borrowing and Lifetimes

References are pointers that lend out the value to others, without
taking ownership.

### Shared References

Shared references are pointers that can be shared. The type is: `&T`.
These can be shared as many times as you'd like and passed around that
many times as well.

```rs
let x = 5;
let y = &x; // shared reference 1, ok.
let z = &x; // shared reference 2, totally ok.
```

### Mutable References

The alternative to a shared reference is a mutable one, `&mut T`. With
mutable references, there is only one active mutable reference allowed,
otherwise there is a compiler error:

```rs
let mut x = 42;
let y = &mut x; // ok, one mutable reference
let z = &x; // ok, one shared reference
dbg!(&y); // not ok, there is already a mutable reference.
```

You can move the value behind a mutable reference:

```rs
fn replace_with_84(s: &mut Box<i32>) {
  // this is not okay, as *s would be empty:
  // let was = *s;
  // but this is:
  let was = std::mem::take(s);
  // so is this:
  *s = was;
  // we can exchange values behind &mut:
  let mut r = Box::new(84);
  std::mem::swap(s, &mut r);
  assert_ne!(*r, 84);
}
let mut s = Box::new(42);
replace_with_84(&mut s);
```

## Interior Mutability

Some types provide _interior mutability_, which allows for mutation of a
value behind a shared reference.

Some types that allow interior mutability are like `Mutex` and
`RefCell`, as they only allow for one mutable reference, and zero shared
references exist. This is built on `UnsafeCell`.

Other categories of types give methods to manipulating the value
contained in place, like `std::sync::atomic` and `std::cell:Cell`.

### Lifetimes

A lifetime is a name for a region of code that some reference must be
valid for.

### Lifetimes and the borrow checker

When a reference with a lifetime `'a` is used, the borrow checker makes
sure that `'a` is still alive.

### Generic Lifetimes

Take this example: `s` and `p` must have generic lifetimes, since this
would make `str_before` unwritable if there was only one lifetime.

```rs
struct StrSplit<'s, 'p> {
  delimiter: &'p str,
  document: &'s str,
}
impl<'s, 'p> Iterator for StrSplit<'s, 'p> {
  type Item = &'s str;
  fn next(&self) -> Option<Self::Item> {
    todo!()
  }
}
fn str_before(s: &str, c: char) -> Option<&str> {
  StrSplit { document: s, delimiter: &c.to_string() }.next()
}
```

### Lifetime Variance

Variance describes what types are subtypes of others. For example,
`&'static str` is a subtype of `&'a str`, so you can pass it to any
function that takes that lifetime.

In lifetimes, if `'b` outlives `'a`, `'b` can be used any place where
`'a` is required.

A type is `covariant` if you can use it in place of a type (like
`'static str` and `'a str`).

Some types are `invariant`, which means you must provide exactly that
type, like `&mut T`. Any type with mutability is generally invariant for
that reason.

`contravariance` comes up for functions. Taking a less strict type is
preferred, so we say that `&'a str` is contravariant to `&'static str`,
since any function that takes an `&'a str` can also take an `&'static str`.

Next: [types](types.md)
