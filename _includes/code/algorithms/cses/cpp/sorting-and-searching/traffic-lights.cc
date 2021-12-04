#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _input = freopen("input.txt", "r", stdin);
auto _output = freopen("output.txt", "w", stdout);
#endif

int main() {
  ll n, x;
  cin >> x >> n;
  multiset<ll> a, b;
  a.insert(0);
  a.insert(x);
  b.insert(x);
  for (int i = 0; i < n; i++) {
    ll k;
    cin >> k;
    auto it = a.upper_bound(k);
    auto it1 = it;
    it1--;
    ll diff = *it - *it1;
    b.erase(b.find(diff));
    a.insert(k);
    b.insert(*it - k);
    b.insert(k - *it1);
    cout << (*b.rbegin()) << " ";
  }
}
