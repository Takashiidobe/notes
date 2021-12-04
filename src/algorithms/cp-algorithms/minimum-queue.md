---
title: minimum-queue
---

Queue\"

Let\'s create a minimum queue as well:

We\'ll do this by simulating a queue using two stacks.

We add new elements to the stack s1, and remove elements from s2. If s2
is empty, we move all elements from s1 to s2, and pop the top.

```cpp
stack<pair<int, int>> s1, s2;

// Find the minimum:
if (s1.empty() || s2.empty()) {
  minimum = s1.empty() ? s2.top().second : s1.top().second;
} else {
  minimum = min(s1.top().second, s2.top().second);
}

// Add an element:
int minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
s1.push({new_element, minimum});

// Removing an element:
if (s2.empty()) {
  while (!s1.empty()) {
    int element = s1.top().first;
    s1.pop();
    int minimum = s2.empty() ? element : min(element, s2.top().second);
    s2.push({element, minimum});
  }
}
int remove_element = s2.top().first;
s2.pop();
```
