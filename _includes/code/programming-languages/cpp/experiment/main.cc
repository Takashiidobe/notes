#include <cstdio>
#include <fmt/core.h>

struct S {
  S() { puts("S()"); }
  S(const S &) { puts("S(const S &)"); }
  S(S &&) { puts("S(S &&)"); }
  S &operator=(const S &) {
    puts("operator=(const S &)");
    return *this;
  }
  S &operator=(S &&) {
    puts("operator=(S &&)");
    return *this;
  }
  ~S() { puts("~S()"); }
};

int main() {
  S s1 = S();
  S s2 = S();
  s1 = s2;
}
