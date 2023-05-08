# Inline

Inline is like `static` or `extern`. It's a linker directive.

`static` means that the name cannot be used in other translation units.
`extern` means that the name will be used by other translation units.
`inline` means the function will be defined multiple times, and to use one definition.

In gcc and clang, generally the linker uses the first definition as the definition to use for all functions:

inline111.cpp
```cpp
#include <iostream>

void bar();
inline int fun() { return 111; }

int main() {
  std::cout << "inline111: fun() = " << fun() << ", &fun = " << (void*) &fun;
  bar();
}
```

inline222.cpp
```cpp
#include <iostream>

inline int fun() { return 222; }

void bar() {
  std::cout << "inline222: fun() = " << fun() << ", &fun = " << (void*) &fun;
}
```

`fun()` is declared twice here, but if you compile like so:

`g++ -std=c++11 inline111.cpp inline222.cpp`

The output is:

```
inline111: fun() = 111, &fun = 0x4029a0
inline222: fun() = 111, &fun = 0x4029a0
```

But if I swap them:

`g++ -std=c++11 inline222.cpp inline111.cpp`

The output is:

```
inline111: fun() = 222, &fun = 0x402980
inline222: fun() = 222, &fun = 0x402980
```

If the function is inlined away, however, the inline loses its meaning:

`g++ -std=c++11 -O2 inline111.cpp inline222.cpp`

```
inline111: fun() = 111, &fun = 0x402900
inline222: fun() = 222, &fun = 0x402900
```

You can use a compiler macro `__attribute__((always_inline));` to force inlining.
