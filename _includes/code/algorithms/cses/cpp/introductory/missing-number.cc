#include <iostream>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  ll s = 0;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int a;
    cin >> a;
    s -= a;
  }
  cout << n * (n + 1) / 2 - s;
}
