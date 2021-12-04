#include <compare>
#include <fmt/core.h>
#include <iostream>

class Data {
private:
  double x;
  double y;
  double z;

public:
  Data(double x, double y, double z) : x(x), y(y), z(z) {}

  const std::strong_ordering operator<=>(const Data &other) const = default;

  friend Data operator+(const Data &d1, const Data &d2) {
    return Data(d1.x + d2.x, d1.y + d2.y, d1.z + d2.z);
  }

  friend Data operator-(const Data &d1, const Data &d2) {
    return Data(d1.x - d2.x, d1.y - d2.y, d1.z - d2.z);
  }

  friend Data operator*(const Data &d1, const Data &d2) {
    return Data(d1.x * d2.x, d1.y * d2.y, d1.z * d2.z);
  }

  friend Data operator/(const Data &d1, const Data &d2) {
    return Data(d1.x / d2.x, d1.y / d2.y, d1.z / d2.z);
  }

  friend std::ostream &operator<<(std::ostream &out, const Data &d) {
    out << fmt::format("Data({}, {}, {})", d.x, d.y, d.z);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Data &data) {
    in >> data.x;
    in >> data.y;
    in >> data.z;

    return in;
  }

  const Data operator-() const { return Data(-x, -y, -z); }
  const Data operator+() const { return Data(+x, +y, +z); }

  double &operator[](int index) {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else if (index == 2) {
      return z;
    } else {
      return z;
    }
  }

  Data &operator++(int) {
    x++;
    y++;
    z++;
    return *this;
  }

  Data &operator--(int) {
    x--;
    y--;
    z--;
    return *this;
  }

  Data &operator++() {
    x++;
    y++;
    z++;
    return *this;
  }

  Data &operator--() {
    x--;
    y--;
    z--;
    return *this;
  }
};

int main() {
  auto d1 = Data{1, 2, 3};
  auto d2 = Data{1, 3, 5};
  auto d3 = d1 + d2;

  std::cout << d1 << '\n';
  std::cout << d2 << '\n';
  std::cout << d3 << '\n';

  ++d3;
  --d3;
  d3++;
  d3--;

  std::cout << d3 << '\n';
  std::cout << d3[0] << '\n';
  std::cout << d3[1] << '\n';
  std::cout << d3[2] << '\n';

  d3[0] = 10;
  d3[1] = 10;
  d3[2] = 10;
  std::cout << d3[0] << '\n';
  std::cout << d3[1] << '\n';
  std::cout << d3[2] << '\n';
}
