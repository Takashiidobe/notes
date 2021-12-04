---
title: polymorphism-in-c
---

In C

# Polymorphism in C

Here\'s a fun little one. Implementing some object oriented features in
pure C. Let\'s have some fun and implement an abstract base class for a
`Node`.

```c
struct Node {
  int value;
  struct Node* next;
};
```

This `Node` is the base class that we will extend later, but we can also
use it as is.

```c
#include <stdio.h>

struct Node {
  int value;
  struct Node* next;
};

int main() {
  struct Node n = {20, NULL};
  printf("%d\n", n.value);
}
```

So let\'s start extending it by making a struct with a function pointer
where we can add to the node value.

Clearly, we could just do something like `n.value += new_value`, but
that\'s so procedural, isn\'t it

```c
#include <stdio.h>

struct Node {
  int value;
  struct Node* next;
};

struct AddableNode {
  struct Node *super;
  void (*add)(struct AddableNode*, int);
}

void add_to_node(struct AddableNode *self, int value) {
  self->super->value += value;
}

int main() {
  struct Node n = {50, NULL};
  struct AddableNode an = {&n, add_to_node};

  an.add(&an, 10);

  printf("%u\n", an.super->value);
}
```

Here we\'ve created a new `AddableNode` struct which takes a pointer to
its base struct (The AddableNode) and a function pointer to add. This
function pointer inside of the struct returns void, calls itself add,
and takes in two paramters, a pointer to an `AddableNode` (self / this),
and a value to add.

We then call the function on the struct with `an.add(&an, 10)`, which is
basically like saying `self.add(self, 10)`, just in a roundabout way.

Now the problem here is that it becomes a bit of a pain to get the value
from the pointer; we would have to do something like
`self->super->value` which is a bit of typing. Why not just make a
method for get and set for our node value too so we don\'t have to type
as much?

```c
#include <stdio.h>

struct Node {
  int value;
  struct Node* next;
};

struct AddableNode {
  struct Node *super;
  void (*add)(struct AddableNode*, int);
  int (*get_value)(struct AddableNode*);
  void (*set_value)(struct AddableNode*, int);
};

void add_to_node(struct AddableNode *self, int _value) {
  self->super->value += _value;
}

int get_node_value(struct AddableNode *self) {
  return self->super->value;
}

void set_node_value(struct AddableNode *self, int _value) {
  self->super->value = _value;
}

int main() {
  struct Node n = {50, NULL};
  struct AddableNode an = {&n, add_to_node, get_node_value, set_node_value};

  an.add(&an, 10);
  an.set_value(&an, 30);

  printf("%u\n", an.get_value(&an));
}
```

I guess `an.get_value(&an);` doesn\'t save much space compared to
`an->super->value`, but its a bit more expressive.

it is a bit of a pain to always instantiate this class, so let\'s make a
factory that takes in a value and returns an AddableNode.

```c
struct AddableNode node_factory(int _value) {
  struct Node n = {_value, NULL};
  struct AddableNode an = {&n, add_to_node, get_node_value, set_node_value};
  return an;
}
```

Here\'s our final code.

```c
#include <stdio.h>

struct Node {
  int value;
  struct Node* next;
};

struct AddableNode {
  struct Node *super;
  void (*add)(struct AddableNode*, int);
  int (*get_value)(struct AddableNode*);
  void (*set_value)(struct AddableNode*, int);
};

void add_to_node(struct AddableNode *self, int _value) {
  self->super->value += _value;
}

int get_node_value(struct AddableNode *self) {
  return self->super->value;
}

void set_node_value(struct AddableNode *self, int _value) {
  self->super->value = _value;
}

struct AddableNode node_factory(int _value) {
  struct Node n = {_value, NULL};
  struct AddableNode an = {&n, add_to_node, get_node_value, set_node_value};
  return an;
}

int main() {
  struct AddableNode an = node_factory(0);
  an.add(&an, 10);
  an.set_value(&an, 30);

  printf("%u\n", an.get_value(&an));
}
```
