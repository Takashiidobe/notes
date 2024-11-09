---
title: Arrays
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:21:43 pm
---

# Arrays

- We can define fixed size arrays in C like so.

```c
int arr[6] = {10,20,30,40,50,60};
```

Visually a memory allocated array looks like this.

![Array.png](/Array.png)

- Arrays can be implemented as **Lists**, or sequentially in memory,
  which we\'ll call plain arrays. These have different tradeoffs.

As a list, it might look like this: ![ArrayList.png](/ArrayList.png)

## Complexity

Worst Case Array List

---

Space O(n) O(n)
Traversal O(n) O(n)
Lookup O(1) O(n)
Append O(1) O(n)
Prepend O(n) O(1)
Insert O(n) O(n)
Delete O(n) O(n)

- Lists are fast at prepending. Arrays are fast at lookup and
  appending.
- Most of the time we\'ll use an array.
- Arrays tend to be faster to traverse and insert/delete into, because
  they are laid out contiguously in memory, whereas list nodes could
  be anywhere in memory.

## Resizing

- Lists do not need to be resized, but Arrays do. The caller can
  reserve as much memory as they might need for their array, but that
  deteriorates performance (more memory usage = less L1/L2/L3 cache
  hits).
- Thus, when arrays are allocated, they generally have a length and a
  capacity.

```c
struct Array {
  int* items;
  size_t length;
  size_t capacity;
}
```

- When the capacity is hit, you have to allocate a bigger array, copy
  over items, and free the previous array. Then, update your pointer
  to the new array, and add the item.

```c
void append(struct Array arr, int value) {
  if (arr.length == arr.capacity) {
    // resize array
    int* new_arr = malloc(sizeof(int) * capacity * 2);
    for (int i = 0; i < arr.length; i++) {
      new_arr[i] = arr[i];
    }
    free(arr->items);
    arr->items = new_arr;
    arr->items[length] = value;
    arr.length++;
    arr.capacity *= 2;
  } else {
    // don't resize array.
    arr.items[length] = value;
    arr.length++;
  }
}
```
