#include "util.h"

template <typename T> class BinaryTree {
private:
  struct Node {
    T value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(T val) { value = val; }
  };
  Node *root = nullptr;
  size_t size = 0;

public:
  BinaryTree() = default;
  BinaryTree(T val) {
    root = new Node(val);
    size = 1;
  }
  void destroy_tree(Node *n) {
    if (n->left != nullptr)
      destroy_tree(n->left);
    if (n->right != nullptr)
      destroy_tree(n->right);
    if (n != nullptr) {
      _print(n->value, "Deleting Node");
      delete n;
    }
  }
  ~BinaryTree() { destroy_tree(root); }
  Node *get_root() {
    assert(root != nullptr);
    return root;
  }
  void add_node(T val) {
    if (root == nullptr) {
      root = new Node{val};
    }
    auto ptr = root;
    while (ptr != nullptr) {
      if (val < ptr->value) {
        if (ptr->left)
          ptr = ptr->left;
        else {
          ptr->left = new Node{val};
          size++;
        }
      } else if (val > ptr->value) {
        if (ptr->right)
          ptr = ptr->right;
        else {
          ptr->right = new Node{val};
          size++;
        }
      } else {
        break;
      }
    }
  }
};

void create_and_destroy_tree() {
  auto b = BinaryTree(10);
  for (int i = 1; i <= 5000; i++) {
    b.add_node(i * 10);
  }
}

int main() { _time(create_and_destroy_tree); }
