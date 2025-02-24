---
title: Iteration Vs Recursion
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Monday, February 24th 2025, 7:23:08 am
---

# Iteration Vs Recursion

In Programming, any task that requires something to be done repeatedly
can be solved either with iteration or recursion.

Iteration is generally done with a for loop, while recursion calls the
same function.

Here\'s how we might print an array iteratively and recursively.

## Iteratively

```c
#include <stdio.h>

int main() {
    int arr[5] = {1,2,3,4,5};
    int length = 5;
    for (int i = 0; i < length; i++) {
        printf("%i\n", arr[i]);
    }
}
```

## Recursively

```c
#include <stdio.h>

void print_all_elements(int* arr, int i, int length) {
    if (i >= length) return;
    else {
        printf("%i\n", arr[i]);
        return print_all_elements(arr, i + 1);
    }
}

int main() {
    int arr[5] = {1,2,3,4,5};
    int length = 5;
    print_all_elements(arr, 0, length);
}
```

### Comparison

- In the case above, it is probably more intuitive to use iteration.
  We print the 0th element, and continue printing until we\'ve printed
  the last element.
- In the recursive case, we make sure we haven\'t gone past the last
  element, then we print the first element, then we print the second
  element, making sure we haven\'t gone past the last element.
- This is a bit more difficult, and wordy in this case.
- We will find some cases later on where recursion is easier to
  express than iteration.
