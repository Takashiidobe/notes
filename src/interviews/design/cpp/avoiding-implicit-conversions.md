---
title: Avoiding Implicit Conversions
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:07:28 pm
---

# Avoiding Implicit Conversions

Implicit conversions in C++ can be avoided by using braced initialization:

```cpp
int x = {3.0}; // compiler error
```

However, in a class, you may want to avoid narrowing conversions as well:

```cpp
class X {
  public:
  X(int x): x_(x) {} // construct with int
  X(const auto x) = delete;
  int x_;
};

int main() {
  X x(5.1); // this uses a float constructor, which has been deleted. Compiler error
}
```
