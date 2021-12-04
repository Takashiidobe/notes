#include <iostream>
#include <memory>

// interface with an overrideable name() function.
// virtuals have to be heap allocated
class Printable {
 public:
  virtual std::string name() = 0;
};

class Entity : public Printable {
 public:
  Entity() { std::cout << "Created\n"; }
  ~Entity() { std::cout << "Destroyed\n"; }
  virtual std::string name() override { return "Name: Entity"; }
};

void Print(Printable* p) { std::cout << p->name() << std::endl; }

int main() {
  // no need to delete here.
  const auto entity = std::make_unique<Entity>();

  // use .get() to get the underlying pointer to pass into a function
  Print(entity.get());
}
