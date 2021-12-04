#include <iostream>
class Cents {
 public:
  Cents(int cents = 0) { cents_ = cents; }
  int getCents() const { return cents_; }
  friend Cents operator+(const Cents &c1, const Cents &c2);
  friend Cents operator-(const Cents &c1, const Cents &c2);
  Cents operator+() const;
  Cents operator-() const;
  bool operator!() const;
  const auto operator<=>(const Cents &c) const = default;
  Cents &operator++();
  Cents &operator--();
  Cents operator++(int);
  Cents operator--(int);

 private:
  int cents_;
};

Cents Cents::operator++(int) {
  ++cents_;
  return *this;
}

Cents Cents::operator--(int) {
  --cents_;
  return *this;
}

Cents &Cents::operator++() {
  cents_++;
  return *this;
}
Cents &Cents::operator--() {
  cents_--;
  return *this;
}

Cents operator+(const Cents &c1, const Cents &c2) {
  return Cents(c1.cents_ + c2.cents_);
}

Cents operator-(const Cents &c1, const Cents &c2) {
  return Cents(c1.cents_ - c2.cents_);
}

Cents Cents::operator+() const {
  return (cents_ >= 0) ? Cents(cents_) : Cents(-cents_);
}
Cents Cents::operator-() const {
  return (cents_ >= 0) ? Cents(-cents_) : Cents(cents_);
}

bool Cents::operator!() const { return this->cents_ != 0; }

int main() {
  Cents cents1{6};
  Cents cents2{8};
  std::cout << cents1.getCents() << std::endl;
  std::cout << cents2.getCents() << std::endl;
  cents1 = -cents1;
  cents2 = -cents2;
  cents1++;
  ++cents1;
  --cents2;
  cents2--;
  std::cout << cents1.getCents() << std::endl;
  std::cout << cents2.getCents() << std::endl;
  Cents centsSum{cents1 + cents2};

  std::cout << std::boolalpha << (cents1 == cents2) << std::endl;
  std::cout << "I have " << centsSum.getCents() << " cents.\n";
}
