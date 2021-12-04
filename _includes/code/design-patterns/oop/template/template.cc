#include <fmt/core.h>
#include <string>

class Vehicle {
public:
  virtual std::string getName() { return name_; }
  virtual int getSpeed() { return speed_; }
  virtual std::string getDestination() { return destination_; }

protected:
  std::string name_ = "Vehicle";
  int speed_ = 0;
  std::string destination_ = "Unknown";
};

class Car : public Vehicle {
public:
  Car(int speed, std::string name, std::string destination)
      : speed_(speed), name_(name), destination_(destination) {}

  std::string getName() { return name_; }
  int getSpeed() { return speed_; }
  std::string getDestination() { return destination_; }

private:
  int speed_;
  std::string name_;
  std::string destination_;
};

class Ship : public Vehicle {
public:
  Ship(int speed, std::string name, std::string destination)
      : speed_(speed), name_(name), destination_(destination) {}

  std::string getName() { return name_; }
  int getSpeed() { return speed_; }
  std::string getDestination() { return destination_; }

private:
  int speed_;
  std::string name_;
  std::string destination_;
};

void printInfo(Vehicle &v) {
  fmt::print("My name is: {}, My speed is: {}, My destination is: {}\n",
             v.getName(), v.getSpeed(), v.getDestination());
}

int main() {
  auto s = Ship(5, "Boat", "Zimbabwe");
  auto c = Car(10, "Car", "Iowa");
  printInfo(s);
  printInfo(c);
}
