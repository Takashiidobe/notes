#include <fmt/core.h>
#include <utility>

class Chair {
public:
  Chair() { fmt::print("Chair created.\n"); }
  virtual ~Chair() { fmt::print("Chair Destroyed.\n"); }
  virtual void use() = 0;
};

class VictorianChair : public Chair {
public:
  VictorianChair() { fmt::print("Victorian Chair created.\n"); }
  ~VictorianChair() { fmt::print("Victorian Chair deleted.\n"); }
  virtual void use() { fmt::print("Using victorian chair\n"); }
};

class ModernChair : public Chair {
public:
  ModernChair() { fmt::print("Modern Chair created.\n"); }
  ~ModernChair() { fmt::print("Modern Chair deleted.\n"); }
  virtual void use() { fmt::print("Using Modern chair\n"); }
};

class CoffeeTable {
public:
  CoffeeTable() { fmt::print("Coffee Table created.\n"); }
  virtual ~CoffeeTable() { fmt::print("Coffee Table Destroyed.\n"); }
  virtual void use() = 0;
};

class VictorianCoffeeTable : public CoffeeTable {
public:
  VictorianCoffeeTable() { fmt::print("Victorian Coffee Table created.\n"); }
  ~VictorianCoffeeTable() { fmt::print("Victorian Coffee Table deleted.\n"); }
  virtual void use() { fmt::print("Using Victorian Coffee Table\n"); }
};

class ModernCoffeeTable : public CoffeeTable {
public:
  ModernCoffeeTable() { fmt::print("Modern Coffee Table created.\n"); }
  ~ModernCoffeeTable() { fmt::print("Modern Coffee Table deleted.\n"); }
  virtual void use() { fmt::print("Using Modern Coffee Table\n"); }
};

class FurnitureFactory {
public:
  FurnitureFactory() { fmt::print("FurnitureFactory created\n"); }
  virtual ~FurnitureFactory() { fmt::print("FurnitureFactory deleted\n"); }
  virtual Chair *create_chair() = 0;
  virtual CoffeeTable *create_coffee_table() = 0;
};

class VictorianFurnitureFactory : public FurnitureFactory {
public:
  VictorianFurnitureFactory() {
    fmt::print("VictorianFurnitureFactory created.\n");
  }
  ~VictorianFurnitureFactory() {
    fmt::print("VictorianFurnitureFactory deleted.\n");
  }
  CoffeeTable *create_coffee_table() override {
    return new VictorianCoffeeTable();
  }
  Chair *create_chair() override { return new VictorianChair(); }
};

class ModernFurnitureFactory : public FurnitureFactory {
public:
  ModernFurnitureFactory() { fmt::print("ModernFurnitureFactory created.\n"); }
  ~ModernFurnitureFactory() { fmt::print("ModernFurnitureFactory deleted.\n"); }
  CoffeeTable *create_coffee_table() override {
    return new ModernCoffeeTable();
  }
  Chair *create_chair() override { return new ModernChair(); }
};

void client(FurnitureFactory &factory) {
  Chair *chair = factory.create_chair();
  CoffeeTable *coffee_table = factory.create_coffee_table();

  chair->use();
  coffee_table->use();

  delete chair;
  delete coffee_table;
}

int main() {
  std::unique_ptr<FurnitureFactory> victorian_factory =
      std::make_unique<VictorianFurnitureFactory>();
  client(*victorian_factory);
  std::unique_ptr<FurnitureFactory> modern_factory =
      std::make_unique<ModernFurnitureFactory>();
  client(*modern_factory);
}
