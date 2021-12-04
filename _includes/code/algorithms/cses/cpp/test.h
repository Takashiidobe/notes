#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <iostream>

auto test_eq = [](auto a, auto b) {
  if (a != b) {
    std::cout << " Failed." << '\n';
  } else {
    std::cout << " Succeeded." << '\n';
  }
};

#endif