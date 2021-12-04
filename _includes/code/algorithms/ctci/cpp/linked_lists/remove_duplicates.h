#include <set>

#include "../test/test.h"
#include "linked_list.h"

namespace linked_lists {
namespace remove_duplicates {
using namespace linked_lists::linked_list;
// remove duplicates by adding them to a std::set, seeing if it contains it, and
// if so, deleting it by moving onto the next elements.
void remove_duplicates(Node* ll) {
  if (ll == nullptr) return;

  auto dups = std::set<int>();

  while (ll != nullptr) {
    if (dups.contains(ll.data)) {
      // delete it here
      if (ll->next != nullptr) {
        Node* temp =
      }
    } else {
      // don't delete it
    }
    ll = ll->next;
  }
}

void test() { test_eq(10, 10); }

}  // namespace remove_duplicates
}  // namespace linked_lists
