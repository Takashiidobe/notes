#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;
  vector<ll> v;
  for (int i = 0; i < n; i++) {
    int x;
    int y;
    cin >> x;
    cin >> y;
    ll z = max(x, y);
    ll ans;
    ll z2 = z * z;
    v.push_back(ans);
  }

  for (auto x : v) cout << x << '\n';
}
