#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

#define SORT(n) sort(n.begin(), n.end())

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  cin >> n;
  vector<ll> vec(n);

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  ll ans = vec[0];
  ll curr = vec[0];

  for (int i = 1; i < n; i++) {
    curr += vec[i];
    curr = max(curr, vec[i]);
    ans = max(ans, curr);
  }

  cout << ans;
}
