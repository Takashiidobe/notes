---
title: deque-in-c
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:23:33 pm
---
You can make a deque in C like this:

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Deque {
    int* items;
    size_t len;
    size_t capacity;
    size_t head;
    size_t tail;
} Deque;

Deque* new_deque(size_t capacity) {
    Deque *d = malloc(sizeof(Deque));
    d->items = malloc(sizeof(int) * capacity);
    d->capacity = capacity;
    d->head = 0;
    d->tail = 0;
    d->len = 0;
    return d;
}

void print_deque(Deque *d) {
    printf(;
    for (int i = d->head, j = 0; j < d->len; i = (i + 1) % (d->capacity), j++) {
        printf("index: %d\n", i);
        printf("%d\n", d->items[i]);
    }
    printf(;
}

void free_deque(Deque *d) {
    free(d->items);
    free(d);
}

void deque_push(Deque *d, int val) {
    assert(d->len < d->capacity);
    d->items[d->tail] = val;
    d->tail = (d->tail + 1) % (d->capacity);
    d->len++;
    print_deque(d);
}

int deque_pop(Deque *d) {
    assert(d->len > 0);
    int res = d->items[d->head];
    d->head = (d->head + 1) % d->capacity;
    d->len--;
    print_deque(d);
    return res;
}

int main() {
    Deque *d = new_deque(3);
    deque_push(d, 10);
    deque_push(d, 20);
    deque_push(d, 30);
    deque_pop(d);
    deque_pop(d);
    deque_push(d, 40);
    deque_push(d, 50);
    free_deque(d);
}
```
