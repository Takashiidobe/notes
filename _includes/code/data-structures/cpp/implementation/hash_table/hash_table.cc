#include "util.h"

template <typename T> class HashTable {
private:
  struct Node {
    T value = NULL;
    Node *next;
  };
  size_t capacity = 10;
  vector<Node> nodes{10};

public:
  HashTable() = default;
  HashTable(size_t capacity) { nodes = vector<Node>{capacity}; }
  void set(T val) {
    auto node = Node{val};
    if (nodes[_hash(val)].value != NULL) {
      nodes[_hash(val)] = node;
    }
  }
  size_t _hash(T val) { return hash<T>()(val) % capacity; }
  void print_items() {
    for (auto node : nodes) {
      cout << node.value << '\n';
    }
  }
};

int main() {
  auto ht = HashTable<int>();
  ht.set(10);
}
