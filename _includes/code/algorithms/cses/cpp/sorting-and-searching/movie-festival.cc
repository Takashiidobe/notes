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
  vector<pair<ll, ll>> v(n);

  const auto cmp = [](const auto &a, const auto &b) {
    return a.second < b.second;
  };

  ll a;
  ll b;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    v[i] = {a, b};
  }

  sort(v.begin(), v.end(), cmp);

  ll ans = 0;

  int curr_event_end = -1;

  for (int i = 0; i < n; i++) {
    if (v[i].first >= curr_event_end) {
      curr_event_end = v[i].second;
      ans++;
    }
  }

  cout << ans;
}
