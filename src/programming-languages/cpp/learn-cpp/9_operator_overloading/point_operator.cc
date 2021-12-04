#include <iostream>

class Point {
 public:
  Point(double x = 0.0, double y = 0.0, double z = 0.0) : x_{x}, y_{y}, z_{z} {}

  double getX() const { return x_; }
  double getY() const { return y_; }
  double getZ() const { return z_; }

  friend std::ostream &operator<<(std::ostream &out, const Point &point);
  friend std::istream &operator>>(std::istream &in, Point &point);

 private:
  double x_;
  double y_;
  double z_;
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << "Point(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ')';

  return out;
}

std::istream &operator>>(std::istream &in, Point &point) {
  in >> point.x_;
  in >> point.y_;
  in >> point.z_;

  return in;
}

int main() {
  Point point1 = {5.0, 6.0, 7.0};
  Point point2 = {6.0, 7.5, 8.0};

  std::cout << point1 << ' ' << point2 << '\n';
}
