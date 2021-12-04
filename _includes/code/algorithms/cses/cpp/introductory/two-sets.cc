#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;
  ll reduce = 0;
  for (ll i = 1; i <= n; i++) reduce += i;

  vector<ll> left;
  ll left_total = 0;
  vector<ll> right;
  ll right_total = 0;

  if (reduce % 2 == 0) {
    for (ll i = n; i > 0; i--) {
      if (left_total < right_total) {
        left_total += i;
        left.push_back(i);
      } else {
        right_total += i;
        right.push_back(i);
      }
    }
    cout << "YES" << '\n';
    cout << left.size() << '\n';
    for (ll e : left) cout << e << " ";
    cout << '\n' << right.size() << '\n';
    for (ll e : right) cout << e << " ";
  } else {
    cout << "NO";
  }
}