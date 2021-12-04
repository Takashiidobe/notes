---
title: minimum-stack
---

Stack\"

Let\'s create a stack where the minimum element of the stack can be
queried in O(1) time.

We can do this by keeping a pair in the stack, with the element and the
minimum in the stack starting from this element.

```cpp
#include <stack>

int main() {
  stack<pair<int, int>> st;
  // adding an element
  int new_min = std.empty() ? new_elem : min(new_elem, st.top().second);
  st.push({new_elem, new_min});
  // removing an element
  int removed_element = st.top().first;
  st.pop();
  // Finding the minimum
  int minimum = st.top().second;
}
```
