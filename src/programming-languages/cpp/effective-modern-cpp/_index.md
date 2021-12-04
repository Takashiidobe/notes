---
title: _index
---

## Chapter 1 Deducing Types

### Item 1: Understand template type deduction

- Since types are now deduced by the compiler in the case of auto, be
  careful about template deduction.

Imagine this:

```cpp
template<typename T>
void f(ParamType param);
```

The type ParamType and the typename T may be the same or different.

In the case below, T is deduced to be `int`, but ParamType is
`const int&`.

```cpp
template<typename T>
void f(const T& param);

int x = 0;
f(x);
```

There are 3 cases
