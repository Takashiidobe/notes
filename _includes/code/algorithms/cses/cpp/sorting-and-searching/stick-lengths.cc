#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

#define LOOP(n) for (int i = 0; i < n; i++)
#define SORT(n) sort(n.begin(), n.end())

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  ll ans = 0;
  cin >> n;
  vector<ll> vec(n);

  LOOP(n) { cin >> vec[i]; }
  SORT(vec);

  ll median = vec[n / 2];

  for (const auto i : vec) {
    ans += abs(median - i);
  }

  cout << ans;
}
