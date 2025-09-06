#include <iostream>

int main() {
  int t;
  std::cin >> t;
  while (t--) {
    long long a, b;
    std::cin >> a >> b;
    long long ans;

    if (a > b) {
      if (a % 2 == 0)
        ans = a * a - b + 1;
      else
        ans = (a - 1) * (a - 1) + b;
    } else {
      if (b % 2 == 0)
        ans = (b - 1) * (b - 1) + a;
      else
        ans = b * b - a + 1;
    }

    std::cout << ans << '\n';
  }
}
