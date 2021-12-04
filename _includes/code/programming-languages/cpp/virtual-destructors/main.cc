#include <fmt/core.h>
#include <utility>

class Base {
public:
  Base() { fmt::print("Creating Base\n"); }
  virtual ~Base() { fmt::print("Base Destroyed\n"); }
};

class Impl : public Base {
public:
  Impl() { fmt::print("Creating Impl\n"); }
  ~Impl() { fmt::print("Impl Destroyed\n"); }
  void use() { fmt::print("Using Impl\n"); }
};

int main() {
  std::unique_ptr<Impl> impl = std::make_unique<Impl>();
  impl->use();
}
