#include <stdio.h>
#include <stdlib.h>

// include insert, search, delete.
// separate chaining and open addressing are the two methods.

struct Node {
  int value;
  struct Node *next;
};

struct Table {
  struct Node *items;
};

struct Table *table_ctor() {
  struct Table *t = (struct Table *)malloc(sizeof(struct Table));
  t->items = (struct Node *)malloc(sizeof(struct Node) * 10);
  return t;
};

void insert_node(struct Node *n, int value) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->value = value;
  new_node->next = n;
  if (n) {
    n->next = new_node;
  }
}

void insert_table(struct Table *t, int value) {
  int hash = value % 10;
  if (t->items[hash] != NULL)
    insert_node(&t->items[hash], value);
  else {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->value = value;
    t->items[hash] = *n;
  }
}

int main() {
  struct Table *t = table_ctor();
  struct Node n = {10, NULL};
  struct Node m = {20, NULL};
  t->items[0] = n;
  t->items[0].next = &m;
  printf("%i\n", t->items[0].next->value);
}
