#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace std::chrono;

void _print(auto item, string s = "Value") { cout << s << ": " << item << endl; }

void _time(auto func) {
  auto start = high_resolution_clock::now();
  func();
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end - start);
  cout << "Execution took: " << duration.count() << " microseconds" << endl;
}
