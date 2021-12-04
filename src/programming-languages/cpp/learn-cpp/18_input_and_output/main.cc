#include <fmt/core.h>

#include <iomanip>
#include <iostream>
#include <string>

int main() {
  std::string strBuf;
  std::getline(std::cin, strBuf);
  fmt::print("{}", strBuf);
}
