#include <iostream>

struct Entity {
  int x = 10;
  void print() const { std::cout << x << std::endl; }
  ~Entity() { std::cout << "Entity is being deleted" << std::endl; }
};

template <typename T> class SmartPointer {
public:
  SmartPointer(T *obj) : obj_(obj) {}
  ~SmartPointer() { delete obj_; }
  T *operator->() { return obj_; }
  const T *operator->() const { return obj_; }

private:
  T *obj_;
};

int main() {
  const SmartPointer<Entity> entity = new Entity();
  entity->print();
}
