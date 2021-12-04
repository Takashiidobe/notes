#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  cin >> n;
  vector<ll> v(n + 1, 0);

  ll a;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    v[a] = i;
  }

  ll ans = 1;

  for (int i = 1; i < n; i++) {
    if (v[i + 1] < v[i]) {
      ans++;
    }
  }

  cout << ans;
}
