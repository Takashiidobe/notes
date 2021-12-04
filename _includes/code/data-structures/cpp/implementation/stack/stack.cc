#include "util.h"

template <class T>
struct Stack
{
private:
  struct Node
  {
    T value;
    Node *next = nullptr;
  };
  Node *head;
  size_t size = 0;

public:
  Stack() = default;
  Stack(T val) { head = new Node{val}; }
  size_t length() { return size; }
  Node *get_head()
  {
    assert(head != nullptr);
    return head;
  }
  void push(T val)
  {
    Node *node = new Node{val};
    if (head == nullptr)
    {
      head = node;
    }
    else
    {
      node->next = head;
      head = node;
    }
    size++;
  }
  Node *pop() { assert(head != nullptr); }
};

int main()
{
  auto stack = Stack(10);
  stack.push(20);
  _print(stack.get_head()->value, "Head Value");
  _print(stack.get_head()->next->value, "Second Node Value");
}
