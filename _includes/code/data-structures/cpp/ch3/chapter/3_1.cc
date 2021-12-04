#include "util.h"

template <class T> class Node {
public:
  Node(T _x) {
    x = _x;
    next = nullptr;
  }
  ~Node() = default;
  T x;
  Node *next;
  Node *head;
  Node *tail;
  int n;

  T push(T x) {
    Node *u = new Node(x);
    u->next = head;
    head = u;
    if (n == 0)
      tail = u;
    n++;
    return x;
  }
};

int main() { cout << "Hello World!" << endl; }
