#include <fmt/core.h>
#include <type_traits>

// SFINAE -> Substitution Failure is not an Error

template <typename Float,
          typename = std::enable_if_t<std::is_floating_point_v<Float>>>
auto add_floats(const Float a, const Float b) {
  return a + b;
}

// Concepts requires syntax
template <typename Float>
auto add_floats_req(const Float a,
                    const Float b) requires std::is_floating_point_v<Float> {
  return a + b;
}

// Concept Syntax
template <typename T> concept is_floating_point = std::is_floating_point_v<T>;

template <is_floating_point Float>
auto add_floats_concepts(const Float a, const Float b) {
  return a + b;
}

int main() {
  fmt::print("{}\n", add_floats(1.0, 1.0));
  fmt::print("{}\n", add_floats_req(1.0, 1.0));
  fmt::print("{}\n", add_floats_concepts(1.0, 1.0));
}
