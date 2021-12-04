#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *next;
};

struct List {
  struct Node *root;
  size_t length;
  void (*push_back)(struct List *self, int _value);
  void (*push_front)(struct List *self, int _value);
  void (*print)(struct List *);
  void (*free)(struct List *self);
};

struct Node *node_ctor(int _value) {
  struct Node *n = (struct Node *)malloc(sizeof(struct Node));
  n->value = _value;
  n->next = NULL;
  return n;
}

void free_list(struct List *self) {
  struct Node *temp;
  struct Node *head = self->root;
  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }
  self->length = 0;
}

void print_list(struct List *self) {
  struct Node *ptr = self->root;
  while (ptr->next) {
    printf("%d\n", ptr->value);
    ptr = ptr->next;
  }
}

void push_back(struct List *self, int _value) {
  struct Node *n = node_ctor(_value);

  if (self->root) {
    struct Node *ptr = self->root;
    while (ptr->next) {
      ptr = ptr->next;
    }
    ptr->next = n;
  } else {
    self->root = n;
  }
  self->length++;
}

void push_front(struct List *self, int _value) {
  struct Node *n = node_ctor(_value);

  if (self->root) {
    n->next = self->root;
    self->root = n;
  } else {
    self->root = n;
  }
  self->length++;
}

struct List list_ctor(int _value) {
  struct Node *n = (struct Node *)malloc(sizeof(struct Node));
  n->value = _value;
  n->next = NULL;
  struct List l = {n, 1, push_back, push_front, print_list, free_list};
  return l;
}

int main() {
  struct List l = list_ctor(0);
  for (int i = 1; i < 11; i++) {
    l.push_front(&l, -i * 10);
  }
  for (int i = 1; i < 11; i++) {
    l.push_back(&l, i * 10);
  }
  l.print(&l);
  l.free(&l);
}
