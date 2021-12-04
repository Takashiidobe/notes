#include <fmt/core.h>
#include <string>

// The builder pattern allows you to construct a class incrementally
class Builder {
public:
  Builder() { fmt::print("Builder being created.\n"); }
  ~Builder() { fmt::print("Builder being destroyed.\n"); }
  Builder &set_x(int _x) {
    x = _x;
    return *this;
  }
  Builder &set_y(int _y) {
    y = _y;
    return *this;
  }
  Builder &set_z(int _z) {
    z = _z;
    return *this;
  }
  Builder &set_s(std::string _s) {
    s = _s;
    return *this;
  }
  Builder &build() { return *this; }
  void print() { fmt::print("x: {}, y: {}, z: {}, s: {}\n", x, y, z, s); }

private:
  int x = 10;
  int y = 20;
  int z = 30;
  std::string s = "Unknown";
};

int main() {
  auto b = Builder().set_x(100).set_y(200).set_z(300).set_s("rocking").build();
  b.print();
}
