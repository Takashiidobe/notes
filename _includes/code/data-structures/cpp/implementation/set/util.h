#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;

void print(auto item, string s = "Value") { cout << s << ": " << item << endl; }

void _time(auto func) {
  auto start = high_resolution_clock::now();
  func();
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end - start);
  cout << "Execution took: " <<  duration.count() << " microseconds" << endl;
}
