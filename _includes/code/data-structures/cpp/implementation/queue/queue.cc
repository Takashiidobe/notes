#include "util.h"

template <typename T> class Queue {
private:
  struct Node {
    T value;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(T val) { value = val; }
  };
  size_t size = 0;
  Node *head = nullptr;
  Node *tail = nullptr;

public:
  Node *get_head() { return head; }
  Node *get_tail() { return tail; }
  size_t length() { return size; }
  Queue() = default;
  Queue(T val) {
    auto node = new Node(val);
    head = node;
    tail = node;
    size = 1;
  }
  ~Queue() {
    while (head != nullptr) {
      delete head;
      head = head->next;
    }
  }
  void enqueue(T val) {
    auto node = new Node(val);
    if (tail == nullptr) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    size++;
  }
  Node *dequeue() {
    assert(head != nullptr);
    auto res = head;
    if (head->next != nullptr) {
      head = head->next;
    } else {
      head = nullptr;
      tail = nullptr;
    }
    size--;
    return res;
  }
};

int main() {
  auto queue = Queue(10);
  queue.enqueue(20);
  _print(queue.get_head()->value, "Head value");
  _print(queue.dequeue()->value, "Dequeued value");
  _print(queue.get_tail()->value, "Tail value");
  _print(queue.length(), "Queue's Length");
}
