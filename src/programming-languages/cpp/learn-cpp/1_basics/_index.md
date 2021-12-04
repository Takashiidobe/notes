---
title: _index
---

`int x` defines a variable named x. `x = 5` assigns 5 to x.

## Direct Initialization

You can use direct initialization like so:

`int width(5);`

which saves copying complex types from the right to the left.

## Uniform initialization

`int width { 5 };` `int height = { 6 };`

You\'ll want to always initialize your variables on creation, and use
uniform initialization.

## User Input

```cpp
#include <iostream>  // for std::cout and std::cin

int main() {
  std::cout << "Enter a number: "; // ask user for a number
  int x{ }; // define variable x to hold user input (and zero-initialize it)
  std::cin >> x; // get number from keyboard and store it in variable x
  std::cout << "You entered " << x << '\n';
  return 0;
}
```

## Undefined Behavior

- The compiler generates code that is not well-defined, which may
  produce different results, crash, or do things differently when
  compiled by different compilers.
