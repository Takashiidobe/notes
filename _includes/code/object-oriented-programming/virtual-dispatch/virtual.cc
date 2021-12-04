#include <stdio.h>

struct Animal {
  virtual const char *name() const { return "Animal"; }
  virtual void move() const { printf("walk %s\n", name()); }
  virtual ~Animal() {}
};

struct Bird : public Animal {
  virtual void move() const override { printf("fly %s\n", name()); }
  virtual const char *name() const override { return "Bird"; }
};

struct Elephant : public Animal {
  virtual const char *name() const override { return "Elephant"; }
};

int main(void) {
  const Animal *animals[] = {new Animal(), new Bird(), new Elephant()};

  for (const auto &animal : animals) {
    animal->move();
  }
}
