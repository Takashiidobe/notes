#include <iostream>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;
  for (ll i = 1; i <= n; i++) {
    ll ans = ((i * i) * (i * i - 1) / 2) - (4 * (i - 1) * (i - 2));
    cout << ans << '\n';
  }
}
