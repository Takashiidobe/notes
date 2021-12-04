#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  ll m;
  multiset<ll, greater<ll>> ticket_prices;
  vector<ll> customer_prices;
  cin >> n >> m;

  ll b;
  for (int i = 0; i < n; i++) {
    cin >> b;
    ticket_prices.insert(b);
  }

  for (int i = 0; i < m; i++) {
    cin >> customer_prices[i];
  }

  for (int i = 0; i < m; i++) {
    auto it = ticket_prices.lower_bound(customer_prices[i]);
    if (it == ticket_prices.end()) {
      cout << -1 << '\n';
    } else {
      cout << *it << '\n';
      ticket_prices.erase(it);
    }
  }
}
