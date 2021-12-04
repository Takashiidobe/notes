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
  vector<ll> vec(n);
  multiset<ll> m;

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  for (const auto i : vec) {
    const auto it = m.upper_bound(i);
    if (it != m.end()) {
      m.erase(it);
    }
    m.insert(i);
  }

  cout << m.size();
}
