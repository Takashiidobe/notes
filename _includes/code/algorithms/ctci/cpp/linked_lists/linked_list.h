#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>

namespace linked_lists {
namespace linked_list {
struct Node {
  Node *next = nullptr;
  int data;
  Node(int d = 0) { data = d; }
  ~Node() {
    Node *temp;
    while (next != nullptr) {
      temp = next->next;
      delete next;
      next = temp;
    }
  }

  void append(int d) {
    auto node = new Node(d);
    Node *n = this;
    while (n->next != nullptr) {
      n = n->next;
    }
    n->next = node;
  }

  void print() {
    std::cout << data << std::endl;
    while (next != nullptr) {
      std::cout << next->data << std::endl;
      next = next->next;
    }
  }
};
}  // namespace linked_list
}  // namespace linked_lists
#endif
