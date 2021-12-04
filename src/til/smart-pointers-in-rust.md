---
title: smart-pointers-in-rust
---

Pointers in Rust\"

# Smart Pointers in Rust

## Boxes

- `Box<T>` places an item of type `<T>` on the heap.

It\'s useful for:

- When you have a type whose size can\'t be known at compile time, and
  you use it in a context where it must be known at compile time.
- When you have a large amount of data and you want to be able to
  transfer ownership without a copy.
- When you want to own a value and you only care that it has a
  specific trait, rather than its type.

### Usage

```rs
use std::box::Box;

fn main() {
    let b = Box::new(5);
    dbg!(b);
}
```

## Rc (Reference Counted Box)

Rc is used for types where there are multiple owners. As such, cloning
it increments the reference count, while dropping it decreases the
reference count.

It is automatically dropped at the end of its scope, or you can
explicitly drop it.

```rs
enum List {
    Cons(i32, Rc<List>),
    Nil,
}

use crate::List::{Cons, Nil};
use std::rc::Rc;

fn main() {
    let a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    println!("count after creating a = {}", Rc::strong_count(&a)); // 1
    let b = Cons(3, Rc::clone(&a));
    println!("count after creating b = {}", Rc::strong_count(&a)); // 2
    {
        let c = Cons(4, Rc::clone(&a));
        println!("count after creating c = {}", Rc::strong_count(&a)); // 3
    }
    let d = Cons(3, Rc::clone(&a));
    println!("count after creating d = {}", Rc::strong_count(&a)); // 3
    drop(d); // drop d
    println!("count after dropping d = {}", Rc::strong_count(&a)); // 2
    println!("count after c goes out of scope = {}", Rc::strong_count(&a)); // 2
}
```

## RefCell

Refcell allows mutable borrows checked at runtime. You can mutate the
value inside a `Refcell<T>` even if it is labeled as immutable.

You can use Refcell with Rc to have multiple owners of data.

```rs
#[derive(Debug)]
enum List {
    Cons(Rc<RefCell<i32>>, Rc<List>),
    Nil,
}

use crate::List::{Cons, Nil};
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil))); // a is 5, the tail of the list.

    let b = Cons(Rc::new(RefCell::new(3)), Rc::clone(&a)); // b is a list of 3 -> a
    let c = Cons(Rc::new(RefCell::new(4)), Rc::clone(&a)); // c is a list of 4 -> a

    *value.borrow_mut() += 10; // add 10 to the tail of the list, a.

    println!("a after = {:?}", a);
    println!("b after = {:?}", b);
    println!("c after = {:?}", c);
}
```
