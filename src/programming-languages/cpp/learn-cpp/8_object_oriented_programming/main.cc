#include <iostream>

// Base class
class Shape {
public:
  // pure virtual function providing interface framework.
  virtual const double getArea() = 0;
  const void setHeight(int h) { height = h; }
  const void setWidth(int w) { width = w; }

protected:
  int width;
  int height;
};

// Derived classes
class Rectangle : public Shape {
public:
  const double getArea() override { return (width * height); }
};

// Derived classes
class Triangle : public Shape {
public:
  const double getArea() override { return (width * height) / 2; }
};

int main(void) {
  Rectangle Rect;
  Triangle Tri;

  Rect.setWidth(5);
  Rect.setHeight(7);

  // Print the area of the object.
  std::cout << "Total Rectangle area: " << Rect.getArea() << std::endl;

  Tri.setWidth(5);
  Tri.setHeight(7);

  // Print the area of the object.
  std::cout << "Total Triangle area: " << Tri.getArea() << std::endl;
}
