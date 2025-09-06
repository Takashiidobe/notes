#include <iostream>
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

  int n, m, k;
  cin >> n >> m >> k;
  vector<ll> people(n);
  vector<ll> apartments(m);

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    cin >> people[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> apartments[i];
  }

  sort(people.begin(), people.end());
  sort(apartments.begin(), apartments.end());

  ll i = 0;
  ll j = 0;

  while (i < n && j < m) {
    if (abs(people[i] - apartments[j]) <= k) {
      ans++;
      i++;
      j++;
    } else if (people[i] < apartments[j]) {
      i++;
    } else {
      j++;
    }
  }

  cout << ans;
}
