---
title: Memory
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:21:49 pm
---

# Memory

Here\'s a simplified diagram of memory, which houses both the stack and
the heap.

![Memory](/Memory.png)

When we add to the stack, the stack grows downward. When we add to the
heap, the heap grows upward.

![MemoryGrowth](/MemoryGrowth.png)

## Stack Allocation

When we create new variables, they go on the stack.

Abstractly, the stack is populated with items that we maintain or own,
such as variables, or function calls.

Let\'s say we allocate a few variables in the C code below.

```c
int main() {
    int x = 5;
  int y = 10;

  int arr[3] = {1,2,3};
}
```

A simple mental model might look something like this:

- Our variable `x` has a value of 5, which is located somewhere in the
  stack.

- Our variable `y` has a value of 10, which is located somewhere in
  the stack.

- Our variable `arr` has 3 elements, `1,2,3`, which are located
  somewhere in the stack.

![StackAllocation](/StackAllocation.png)

## Heap Allocation

The heap houses items that are not under our **direct** control.

We can directly put items on the heap and point to them.

Below, the variable x is on the stack, pointing to the value 5 on the
heap.

```c
int main() {
    int *x = 5;
}
```

![HeapAllocation](/HeapAllocation.png)
