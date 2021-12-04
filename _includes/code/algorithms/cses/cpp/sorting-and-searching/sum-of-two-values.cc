#include <iostream>
#include <map>
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

  ll n, x;
  cin >> n >> x;
  map<ll, ll> m;

  ll b;
  for (int i = 0; i < n; i++) {
    cin >> b;
    if (m[b]) {
      cout << m[b] << ' ' << i + 1;
      return 0;
    } else {
      m[x - b] = i + 1;
    }
  }

  cout << "IMPOSSIBLE";
}
