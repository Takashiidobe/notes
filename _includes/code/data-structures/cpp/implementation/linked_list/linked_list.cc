#include "util.h"

template <typename T> class LinkedList {
private:
  struct Node {
    T value;
    Node *next = nullptr;
  };
  Node *root = nullptr;
  size_t length = 0;

public:
  LinkedList() = default;
  LinkedList(T value) { root = new Node{value}; };
  ~LinkedList() {
    while (root != nullptr) {
      delete root;
      cout << "Deleting node with value: " << root->value << endl;
      root = root->next;
    }
  }
  T get_root_value() {
    assert(root != nullptr);
    return root->value;
  }
  size_t size() { return length; }
  void r_push(T value) {
    auto node = new Node{value};
    Node *ptr = root;
    while (ptr->next != nullptr) {
      ptr = ptr->next;
    }
    length++;
    ptr->next = node;
  }
  T r_pop() {
    assert(root != nullptr);
    T popped = root->value;
    delete root;
    if (root->next == nullptr) {
      root = nullptr;
    } else {
      root = root->next;
    }
    length--;
    return popped;
  }
};

int main() {
  auto ll = LinkedList{10};
  _print(ll.r_pop());
}
