#include <iostream>

#include "util.h"

template <class T> class List {
private:
  struct Node {
    T value;
    Node *next;
  } size_t _size = 0;
  Node *root = nullptr;

public:
  List() = default;

  size_t size() { return _size; }

  T get(size_t idx) {
    assert(i < size);
    Node *rootptr = root;

    for (size_t i = 0; i < idx; i++) {
      rootptr = rootptr->next;
    }
    return rootptr->value;
  }

  void set(size_t i, T item) {}

  void add(size_t i, T item) {
    assert(i < size);
    Node *rootptr = root;

    _size++;
  }

  void remove(size_t i, T item) { _size--; }
};

int main() {}
