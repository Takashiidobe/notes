#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

auto problem(vector<ll> nums) {
  vector<vector<ll>> answer = {{}};
  for (auto num : nums) {
    auto temp = answer;
    for (auto n : temp) {
      n.push_back(num);
    }
    answer.push_back(temp);
  }
  answer
}