#include <iostream>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  int x;
  cin >> x;

  ll steps = 0;
  ll max_digit = 0;

  while (x > 0) {
    for (const ll c : to_string(x)) {
      max_digit = max(max_digit, c - '0');
    }
    x -= max_digit;
    steps++;
    max_digit = 0;
  }

  cout << steps;
}
