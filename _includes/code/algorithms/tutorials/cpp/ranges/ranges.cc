#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
  vector<int> ints{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto even = [](int i) { return 0 == i % 2; };

  for (int i : ints | std::ranges::views::filter(even)) {
    cout << i << ' ';
  }
  cout << endl;

  using std::ranges::sort;

  vector<int> v = {5, 6, 7, 1, 2, 3, 4, 8, 9};
  sort(v);

  for (const auto elem : v) {
    cout << elem << ' ';
  }

  auto total = partial_sum(v);

  cout << total << endl;
}
