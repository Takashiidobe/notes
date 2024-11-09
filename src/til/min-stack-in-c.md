---
title: min-stack-in-c
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, November 9th 2024, 7:19:43 am
---

```c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int val;
    int min;
} Node;

typedef struct Stack {
    Node** nodes;
    size_t len;
    size_t capacity;
} Stack;

Stack* new_stack(size_t capacity) {
    Stack *s = malloc(sizeof(Stack));
    s->nodes = malloc(sizeof(Node) * capacity);
    s->len = 0;
    s->capacity = capacity;
    return s;
}

int stack_min(Stack* s) {
    if (s->len == 0) { return -1; }
    return s->nodes[s->len - 1]->min;
}

void stack_push(Stack* s, int val) {
    assert(s->len < s->capacity);
    Node* n = malloc(sizeof(Node));
    n->val = val;
    if (s->len == 0) {
        n->min = val;
    } else {
        n->min = val > s->nodes[s->len - 1]->min ? s->nodes[s->len - 1]->min : val;
    }
    s->nodes[s->len] = n;
    s->len++;
}

int stack_pop(Stack* s) {
    assert(s->len > 0);
    s->len--;
    int popped = s->nodes[s->len]->val;
    free(s->nodes[s->len]);
    return popped;
}

void free_stack(Stack *s) {
    for (int i = 0; i < s->len; i++)
        free(s->nodes[i])
    free(s);
}

int main() {
    Stack *s = new_stack(10);
    stack_push(s, 20);
    printf("The minimum of the stack is: %d\n", stack_min(s));
    stack_push(s, 10);
    printf("The minimum of the stack is: %d\n", stack_min(s));
    printf("Popped from stack: %d\n", stack_pop(s));
    printf("The minimum of the stack is: %d\n", stack_min(s));
    free_stack(s);
}
```
