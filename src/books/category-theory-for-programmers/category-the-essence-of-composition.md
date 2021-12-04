---
title: category-the-essence-of-composition
---

: The Essence of Composition"

Next:
[types-and-functions](types-and-functions.md)

# Category: The Essence of Composition

A Category consists of **objects** and **arrows** that go between them.
An object can be represented with a circle, and an arrow is just an
arrow. Arrows compose, so if you have an arrow from object A to object
B, and another arrow from object B to object C, you get their
composition, that goes from A to C.

## Arrows as Functions

Arrows, which are also called **morphisms** can be thought of as
functions. Let's say you have a function `f` which takes an argument of
type `A` and returns a `B`. You have another function that takes a `B`
and returns a `C`. You can compose them by passing the result of `f` to
`g`. You have just defined a new function that takes an `A` and returns
a `C`.

In Math, this looks like this: `𝑔 ∘ 𝑓`. In Unix, this is like so:
`lsof | grep Chrome` to see all the files Chrome is using.

In C that looks like this:

```c
B f(A a);
C g(B b);
```

The composition looks like:

```c
C compose(A a) {
  return g(f(a));
}
```

In Haskell:

```hs
f :: A -> B
g :: B -> C
```

The composition is:

```hs
g . f
```

## Properties of Composition

There are two properties that the composition in any category must
satisfy:

1.  Composition is associative. If you have three morphisms, `f`, `g`,
    and `h`, that can be composed, you don't need parentheses to
    compose them.

`ℎ ∘(𝑔 ∘ 𝑓) = (ℎ ∘ 𝑔)∘ 𝑓 = ℎ ∘ 𝑔 ∘ 𝑓`

In Haskell:

```hs
f :: A -> B
g :: B -> C
h :: C -> D
h . (g . f) == (h . g) . f == h . g . f
```

2.  For every object `A` there is an arrow which is a unit of
    composition. This arrow loops from the object to itself. This is the
    identity function.

In C++, this would be a template.

```cpp
template<class T> T id (T x) { return x; }
```

In Haskell, the identity function is in the prelude, called `id`.

```hs
id :: a -> a
id x = x
```

Neutral values like `zero` for numbers or `id` are useful when working
with symbolic variables. The identity function becomes very handy as an
argument to, or a return from, a higher-order function.

## Composition is the Essence of Programming

We can only keep about 7 plus or minus 2 things in our mind at any given
time. We need structure to deal with more complicated problems.
Likewise, we need chunks which have a surface area that increases slower
than their volume. Category theory is extreme in that it discourages us
from looking inside the objects. In OOP, all you should have to do is
look at the interface to see what an object does. Likewise, in
functional programming, you should only need to look at the return type
to see what it does. Once you look inside the body, you lose the
advantage of the paradigm.

## Challenges

1.  Implement the identity function in your favorite language.

Rust has an identity function, `std::convert::identity`.

```rs
pub const fn identity<T>(x: T) -> T
```

2.  Implement the composition function in your favorite language. It
    takes two functions as arguments and returns a function that is
    their composition.

```rs
fn<A,B> f(a: A) -> B {
  B
}

fn <B,C> g(b: B) -> C {
  C
}

fn <A,B,C> compose(f: fn_once, g: fn_once, a: A) -> C {
  g(f(a))
}
```

3.  Write a program that tries to test that your composition function
    respects identity.

```rs
assert_eq!(compose(identity, f(a))(5), 9);
```

4.  Is the world-wide web a category in any sense? Are links morphisms?

Web pages are objects and links are morphisms. Links can self-refer
(they respect the identity function) and they can go to other web pages.

5.  Is Facebook a category, with people as objects and friendships as
    morphisms?

No, because `A -> B` and `B -> C` does not imply `A -> C`. If I have a
friend `B`, then `A -> B`. And if they have a friend `C`, then `B -> C`.
But `C` does not have to be friends with me, `A`, so `A !-> C`.

6.  When is a directed graph a category?

When every node has an edge that refers back to it, and for every node
pair `(A, B)` there is a path from `A` to `B`.

Next:
[types-and-functions](types-and-functions.md)
