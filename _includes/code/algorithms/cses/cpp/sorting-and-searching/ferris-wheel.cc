#include <functional>
#include <iostream>
#include <set>

using namespace std;

using ll = long long;

constexpr ll MAX_ALLOWED_WEIGHT = 10e9;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll children_count;
  ll allowed_weight;
  multiset<ll, greater<ll>> children;
  cin >> children_count;
  cin >> allowed_weight;

  ll ans = 0;

  ll b;
  for (int i = 0; i < children_count; i++) {
    cin >> b;
    children.insert(b);
  }

  while (!children.empty()) {
    const auto first_child = children.lower_bound(MAX_ALLOWED_WEIGHT);
    const ll first_child_value = *first_child;

    children.erase(first_child);

    const auto second_child =
        children.lower_bound(allowed_weight - first_child_value);

    if (second_child != children.end()) {
      children.erase(second_child);
    }
    ans++;
  }

  cout << ans;
}
