#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
  void (*free)(struct Node *);
};

void free_node(struct Node *self) { free(self); }

struct Node *node_ctor(int _value) {
  struct Node *n = (struct Node *)malloc(sizeof(struct Node));
  n->value = _value;
  n->left = n->right = n->parent = NULL;
  n->free = free_node;
  return n;
}

struct Tree {
  struct Node *root;
  void (*add)(struct Tree *, int);
  bool (*has)(struct Tree *, int);
  void (*free)(struct Tree *);
  void (*print)(struct Tree *);
};

void free_nodes(struct Node *self) {
  if (self->left)
    free_node(self->left);
  if (self)
    free(self);
  if (self->right)
    free_nodes(self->right);
}

void free_tree(struct Tree *self) { free_nodes(self->root); }

void add_node(struct Tree *self, int _value) {
  struct Node *n = node_ctor(_value);
  if (!self->root)
    self->root = n;
  else {
    struct Node *ptr = self->root;
    while (ptr) {
      if (ptr->value == _value) {
        break;
      } else if (ptr->value > _value) {
        if (!ptr->left) {
          ptr->left = n;
          n->parent = ptr;
        } else {
          ptr = ptr->left;
        }
      } else if (ptr->value < _value) {
        if (!ptr->right) {
          ptr->right = n;
          n->parent = ptr;
        } else {
          ptr = ptr->right;
        }
      }
    }
  }
}

bool node_eq(struct Node *n, int value) {
  if (n && n->value) {
    if (n->value == value)
      return true;
    else if (n->value < value)
      node_eq(n->right, value);
    else if (n->value > value)
      node_eq(n->left, value);
  }
  return false;
}

bool has_node(struct Tree *self, int value) {
  struct Node *ptr = self->root;
  return node_eq(ptr, value);
}

void print_nodes(struct Node *ptr) {
  if (ptr->left)
    print_nodes(ptr->left);
  printf("value is: %i\n", ptr->value);
  if (ptr->right)
    print_nodes(ptr->right);
}

void print_tree(struct Tree *self) {
  struct Node *ptr = self->root;
  print_nodes(ptr);
}

struct Tree tree_ctor(int _value) {
  struct Node *n = node_ctor(_value);
  struct Tree t = {n, add_node, has_node, free_tree, print_tree};
  return t;
}

int main() {
  struct Tree tree = tree_ctor(30);
  tree.add(&tree, 40);
  tree.add(&tree, 20);
  tree.add(&tree, 15);
  tree.add(&tree, 45);
  tree.add(&tree, 35);
  tree.add(&tree, 25);
  tree.print(&tree);
  bool has_30 = tree.has(&tree, 30);
  bool has_25 = tree.has(&tree, 25);
  bool has_40 = tree.has(&tree, 40);

  if (has_30)
    printf("thirty is in the tree\n");
  if (has_25)
    printf("twenty-five is in the tree\n");
  if (has_40)
    printf("forty is in the tree.\n");
  tree.free(&tree);
}
