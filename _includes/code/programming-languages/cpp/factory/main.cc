#include <fmt/core.h>

class Product {
public:
  virtual ~Product() { fmt::print("Destroying product.\n"); }
  virtual void use() = 0;
};

class Pencil : public Product {
public:
  Pencil() { fmt::print("Creating Pencil.\n"); }
  ~Pencil() { fmt::print("Destroying Pencil.\n"); }
  void use() { fmt::print("Using Pencil.\n"); }
};

class Pen : public Product {
public:
  Pen() { fmt::print("Creating Pen.\n"); }
  ~Pen() { fmt::print("Destroying Pen.\n"); }
  void use() { fmt::print("Using Pen.\n"); }
};

class Creator {
public:
  Creator() { fmt::print("Creating Creator.\n"); }
  virtual ~Creator() { fmt::print("Destroying Creator.\n"); }
  virtual Product *create() = 0;
};

class PencilCreator : public Creator {
public:
  PencilCreator() { fmt::print("Creating PencilCreator.\n"); }
  ~PencilCreator() { fmt::print("Destroying PencilCreator.\n"); }
  Product *create() { return new Pencil(); };
};

class PenCreator : public Creator {
public:
  PenCreator() { fmt::print("Creating PenCreator.\n"); }
  ~PenCreator() { fmt::print("Destroying PenCreator.\n"); }
  Product *create() { return new Pen(); };
};

int main() {
  auto pencil = PencilCreator().create();
  auto pen = PenCreator().create();
  pencil->use();
  pen->use();
}
