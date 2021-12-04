#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  int *items;
  size_t length;
  struct Node *left;
  struct Node *right;
};

struct Node *node_ctor() {
  struct Node *node = malloc(sizeof(struct Node));
  node->items = malloc(sizeof(int) * 8);
  node->length = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void node_free(struct Node *n) {
  free(n->items);
  free(n);
}

struct Btree {
  struct Node *root;
};

struct Btree *btree_ctor(int val) {
  struct Btree *tree = malloc(sizeof(struct Btree));
  struct Node *root = node_ctor();
  root->items[0] = val;
  root->length++;
  tree->root = root;
  return tree;
}

void push(struct Btree *tree, int val) {
  if (tree->root == NULL) {
    struct Node *root = node_ctor();
    tree->root = root;
    root->items[0] = val;
    root->length++;
  }
}

int main() {
  struct Btree *tree = btree_ctor(10);
  printf("%i\n", tree->root->items[0]);
}
