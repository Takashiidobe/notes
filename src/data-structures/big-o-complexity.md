---
title: big-o-complexity
---

O Complexity

# Big O Complexity

Big O notation loosely measures how long an algorithm takes to run.

This is done **Relative to the size of input**.

First we have to answer why an absolute measurement (e.g. time) fails
us.

## Time isn\'t good enough

Let\'s say I have a fast computer that can do 1 billion operations per
second. We\'ll abbreviate this to be 1B ops/s.

Let\'s say my friend has a slower computer than can do 1 million
operations per second. We\'ll abbreviate this to be 1M ops/s.

To me, if I run an algorithm that prints out every element of an array
like the below:

```c
void print_all_elements (int* arr, int length) {
    for (int i = 0; i < length; i++) {
    printf("%i\n", arr[i]);
  }
}
```

This algorithm will run 1000x times faster for me than for my friend.

If we both benchmark our code, and find that printing out 1 billion
elements takes 1 second for me and 1000 seconds for my friend, we\'ve
only found out how fast the algorithm is **on our own computer**.

If another friend wanted to check out how fast this algorithm would run,
they would have to transfer it to their computer and benchmark it.

We need something that isn\'t bound to how fast our computer is, and
that something is **Big O Notation**.

## Big O Notation

Big O Notation doesn\'t care about how fast your computer is or my
computer is, because it doesn\'t care for an **absolute** notion of
time, like benchmarks do.

It calculates how fast a specific algorithm is with regards to its
**input size**.

We want to see how much **work** an algorithm does when its input
(abbreviated as n) increases.

Big O Complexity cares about:

- How fast the runtime grows relative to its input
- When the input is extremely large (millions, billions, trillions).

### Constant Time

Constant time means that no matter how large the input size is, the
algorithm always does the same amount of work.

Here\'s an example:

```c
void print_first_element (int* arr) {
  printf("%i\n", arr[0]);
}
```

Regardless of if the array has 1 element or 10 million elements, this
algorithm will operate at the same relative speed, O(1), or constant
time.

This is because all it needs is the address of the first element, finds
what is located there, and returns it.

### Linear Time

Linear time means that as the input size grows, the algorithm has to do
more work for each piece of input.

We\'ll use the example from above:

```c
void print_all_elements (int* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%i\n", arr[i]);
    }
}
```

Now it does matter how many elements there are in the array. If I have
one element in the array, I have to print the first element. If I have
two elements in the array, I have to print the first element and the
second element. If I have a million elements in the array, I have to
print out the first to the millionth element.

## Big O Complexity Visualized

![BigOComplexity](/BigOComplexity.png)
