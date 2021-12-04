#include <fmt/core.h>
#include <string>

enum struct Values {
  value1 = 1,
  value2 = 2,
};

std::string to_string(const Values v) {
  using enum Values;
  switch (v) {
  case value1:
    return "value1";
  case value2:
    return "value2";
  }

  return "unknown value";
}

int main() {
  Values v = Values::value1;
  fmt::print("{}", to_string(v));
}
