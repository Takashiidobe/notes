#include <iostream>

int main() {
  std::cout << "Enter an integer: ";

  int num{0};       // define variable num as an integer variable
  std::cin >> num;  // get integer value from user's keyboard

  int doubled_num = num * 2;

  std::cout << "The number doubled is: " << doubled_num << '\n';

  return 0;
}
