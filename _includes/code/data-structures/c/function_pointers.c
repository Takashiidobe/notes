#include <stdio.h>

struct Node {
  int value;
  struct Node *next;
};

struct AddableNode {
  struct Node *super;
  void (*add)(struct AddableNode *, int);
  int (*get_value)(struct AddableNode *);
  void (*set_value)(struct AddableNode *, int);
};

void add_to_node(struct AddableNode *self, int _value) {
  self->super->value += _value;
}

int get_node_value(struct AddableNode *self) { return self->super->value; }

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
