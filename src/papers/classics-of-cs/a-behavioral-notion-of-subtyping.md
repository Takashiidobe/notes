---
title: A Behavioral Notion of Subtyping
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:35:04 pm
---

# A Behavioral Notion of Subtyping

Behavioral subtyping is the principle that subclasses should satisfy the
expectations of clients accessing subclass objects through references of
the superclass type.

For example, in C++:

```c++
class X {};

class Y : public X {};

X* x = Y{};
```

Y should be treatable as its superclass(es), but it must also retain its
behavioral (implied) characteristics.

For example, if the Bag classes interface supports a get and a put,
where the get pops and returns a random item from the collection, and
put places an item in the bag, then if we subclass Bag with Queue and
Stack types, that's fine -- we can treat Stacks and Queues as Bags.

```c++
class Bag {
  int get() = 0; // get random item from collection
  void put(int x) = 0; // put item in bag
};

class Queue : public Bag {
  int get() { return item.popleft(); }
  void put(int x) { item.push_back(x); }
};

class Stack : public Bag {
  int get() { return item.pop(); }
  void put(int x) { item.push_back(x); }
};

Bag* s = new Stack(); // this is fine, because a stack and queue support
// the implicit interface of a Bag.
```

However, if we subclass Queue from Stack or vice versa, stacks and
queues would not work, as they don't have the same characteristics (LIFO
!= FIFO).

This is an informal rule, but nonetheless is a good ideal to ascribe to.
