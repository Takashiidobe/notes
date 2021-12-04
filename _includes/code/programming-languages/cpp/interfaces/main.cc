#include <fmt/core.h>

// interface
class Animal {
public:
  ~Animal() {}
  virtual void talk() { fmt::print("I'm an animal\n"); }

  virtual void say_age() = 0;

protected:
  int age = 10;
};

class Dog : public Animal {
public:
  void talk() { fmt::print("I'm a dog\n"); }
  void say_age() { fmt::print("This dog is: {} years old.\n", age); }

protected:
  int age = 15;
};

class Pomeranian : public Dog {
public:
  void talk() { fmt::print("I'm a pomeranian\n"); }
  void say_age() { fmt::print("This Pomeranian is: {} years old.\n", age); }

protected:
  int age = 20;
};

int main() {
  Animal a = Dog();
  a.talk();

  Dog d = Dog();
  d.say_age();
  d.talk();

  Pomeranian p = Pomeranian();
  p.say_age();
  p.talk();

  Dog pom = (Dog)Pomeranian();
  pom.say_age();
  pom.talk();
}
