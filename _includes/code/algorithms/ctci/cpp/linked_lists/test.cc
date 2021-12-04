#include <iostream>

#include "linked_list.h"

int main() {
  using namespace linked_lists::linked_list;
  auto ll = Node();
  ll.append(10);
  ll.print();
}
