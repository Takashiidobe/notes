# Variadic Templates

Variadic templates can be instantiated with any number of template arguments:

```cpp
Tuple<> t0;           // Types contains no arguments
Tuple<int> t1;        // Types contains one argument: int
Tuple<int, float> t2; // Types contains two arguments: int and float
Tuple<0> t3;          // error: 0 is not a type
```

Variadic templates with fold expressions allow you to apply the arguments to a unary or binary operator:

```cpp
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}
```

And can be if constexpr to work on zero or more types:

```cpp
template <typename T, typename... Types>
void print(T first, Types... args) {
  std::cout << first << ' ';
  if constexpr(sizeof...(args) > 0) {
    print(args...);
  }
}
```

We can also use if constexpr to overload a function to make one branch be taken at compile time.

```cpp
void add(auto& coll, const auto& val) {
  // call push_back on val if possible.
  if constexpr(requires { coll.push_back(val); }) {
    coll.push_back(val);
  } else {
    coll.insert(val);
  }
}
```
