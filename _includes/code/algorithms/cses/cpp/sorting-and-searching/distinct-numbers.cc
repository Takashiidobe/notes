#include <algorithm>
#include <iostream>
#include <set>

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
  set<ll> s;

  ll b;
  for (int i = 0; i <= n; i++) {
    cin >> b;
    s.insert(b);
  }

  cout << s.size();
}
