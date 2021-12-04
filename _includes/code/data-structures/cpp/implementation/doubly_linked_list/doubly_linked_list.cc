#include "util.h"

template <typename T> class LinkedList {
private:
  struct Node {
    T value;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(T val) : value(val) {}
  };
  size_t size = 0;
  Node *head = nullptr;
  Node *tail = nullptr;

public:
  LinkedList() = default;
  LinkedList(T value) {
    auto node = new Node{value};
    tail = node;
    head = node;
    size = 1;
  }
  Node *get_head() {
    assert(head != nullptr);
    return head;
  }
  Node *get_tail() {
    assert(tail != nullptr);
    return tail;
  }
  size_t get_size() { return size; }
  void r_push(T value) {
    auto node = new Node{value};
    if (head == nullptr) {
      tail = node;
      head = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    size++;
  }
  void l_push(T value) {
    auto node = new Node{value};
    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      node->next = head;
      head->prev = node;
      head = node;
    }
    size++;
  }
  Node *l_pop() {
    assert(head != nullptr);
    auto result = head;
    head = head->next;
    head->prev = nullptr;
    size--;
    return result;
  }
  Node *r_pop() {
    assert(tail != nullptr);
    auto result = tail;
    tail = tail->prev;
    tail->next = nullptr;
    size--;
    return result;
  }
};

int main() {
  LinkedList ll = LinkedList(10);
  for (int i = 1; i < 5; i++)
    ll.r_push((i + 1) * 10);
  ll.l_push(0);
  _print(ll.get_head()->value, "Head Node Value");
  _print(ll.get_head()->next->value, "Second Node Value");
  _print(ll.get_tail()->value, "Tail Value");
  _print(ll.get_size(), "Size");
}
