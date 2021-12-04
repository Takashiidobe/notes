#include <fmt/core.h>
#include <utility>

class Target {
public:
  virtual ~Target() { fmt::print("Target Destroyed.\n"); }
  virtual std::string request() { return "Target request."; }
};

class Adaptee {
public:
  std::string adaptee_request() { return "Adaptee request."; }
};

class Adapter : public Target, public Adaptee {
public:
  ~Adapter() { fmt::print("Adapter Destroyed.\n"); }
  std::string request() override { return adaptee_request(); }
};

void client(Target &target) { fmt::print("{}\n", target.request()); }

int main() {
  std::unique_ptr<Target> target = std::make_unique<Adapter>();
  client(*target);
}
