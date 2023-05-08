# Structured Bindings

Structured bindings allow you to initialize multiple entries by the elements or members of an object:

```cpp
struct MyStruct {
  int i = 0;
  std::string s = "default";
};

MyStruct ms;
auto [u, v] = ms;
```

This can be used to make handling return values easier in maps:

```cpp
std::map<std::string, int> coll;

auto [pos,ok] = coll.insert({"new",42});
if (!ok) {
  // if insert failed, handle error using iterator pos:
}
```

To implement structured bindings for your own type:

```cpp
#include <iostream>
#include <utility>
#include <string>
using namespace std;

class Customer {
private:
    std::string first;
    std::string last;
    long val;
public:
    Customer (std::string f, std::string l, long v)
    : first(std::move(f)), last(std::move(l)), val(v) {
    }
    std::string getFirst() const {
        return first;
    }
    std::string getLast() const {
        return last;
    }
    long getValue() const {
        return val;
    }
};

// provide a tuple-like API for class Customer for structured bindings:
template<>
struct std::tuple_size<Customer> {
  static constexpr int value = 3; // we have 3 attributes
};
template<>
struct std::tuple_element<2, Customer> {
  using type = long; // last attribute is a long
};
template<std::size_t Idx>
struct std::tuple_element<Idx, Customer> {
  using type = std::string; // the other attributes are strings
};
// define specific getters:
template<std::size_t> auto get(const Customer& c);
template<> auto get<0>(const Customer& c) { return c.getFirst(); }
template<> auto get<1>(const Customer& c) { return c.getLast(); }
template<> auto get<2>(const Customer& c) { return c.getValue(); }

int main() {
    auto [first, last, val] = Customer("first", "second", 10);
}
```
