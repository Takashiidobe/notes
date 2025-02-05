---
title: What Does nodiscard Do?
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:07:50 pm
---
# What Does [[nodiscard]] Do?

Nodiscard is a C++ attribute that makes it so the return type of something must be used.

Imagine that you call a function for its side-effects, but it returns a bool for success/failure.

```cpp
bool do_something() {
  auto worked_out = do_something_else();
  if (worked_out) {
    return true;
  } else {
    return false;
  }
}
```

Without `[[nodiscard]]`, the caller gets no warning if they discard the returned type:

```cpp
do_something(); // this is fine.
```

With nodiscard, however:

```cpp
[[nodiscard]] bool do_something() {
  auto worked_out = do_something_else();
  if (worked_out) {
    return true;
  } else {
    return false;
  }
}

do_something(); // this generates a compiler error
auto res = do_something(); // this does not.
```
