#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <iostream>

using namespace std;

auto num = 1;

static auto test_eq = [](auto a, auto b, string name = "Test") {
  if (a != b) {
    cout << std::boolalpha << name << " " << num << " Failed." << endl;
    assert(a == b);
  } else {
    cout << name << " " << num << " Succeeded." << endl;
  }
  num++;
};
#endif
