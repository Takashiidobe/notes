# Spaceship operator

The spaceship operator overloads all relation and equality operators for a class. It is a new feature in C++20:

```cpp
#include <iostream>
#include <compare>
using namespace std;

class Value {
private:
  long id;
public:
  constexpr Value(long i) noexcept : id{i} { }
  auto operator<=> (const Value& rhs) const = default;
};


int main() {
    Value v1 = {5};
    Value v2 = {10};

    cout << (v1 == v2) << '\n'; // 0
    cout << (v1 != v2) << '\n'; // 1
    cout << (v1 < v2) << '\n';  // 1
    cout << (v1 <= v2) << '\n'; // 1
    cout << (v1 > v2) << '\n';  // 0
    cout << (v1 >= v2) << '\n'; // 0
}
```
