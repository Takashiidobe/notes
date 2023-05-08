# Concepts

Concepts allow functions, class templates, and function templates to be constrainted by some binary condition:

```cpp
template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};
 
// Constrained C++20 function template:
template<Hashable T>
void f(T) {}
```
