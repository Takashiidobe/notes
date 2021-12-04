#include <array>
#include <fmt/core.h>
#include <vector>

// turn static const into constexpr
static const std::vector v{1, 2, 3, 4, 5};

static constexpr std::array<int, 5> arr = {1, 2, 3, 4, 5};

int main() {
  for (const auto i : v)
    fmt::print("{}\n", i);
  for (const auto i : arr)
    fmt::print("{}\n", i);
}
