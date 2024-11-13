---
title: Concepts
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:07:25 pm
---
# Concepts

Concepts allow functions, class templates, and function templates to be constrained by some binary condition:

```cpp
template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};
 
// Constrained C++20 function template:
template<Hashable T>
void f(T) {}
```
