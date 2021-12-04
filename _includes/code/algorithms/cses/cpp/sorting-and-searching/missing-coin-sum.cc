#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  int n;
  cin >> n;

  vector<ll> coins(n);

  for (int i = 0; i < n; i++) {
    cin >> coins[i];
  }

  sort(coins.begin(), coins.end());

  ll curr_sum = 0;
  for (int i = 0; i < n; i++) {
    if (curr_sum + 1 < coins[i])
      break;
    curr_sum += coins[i];
  }
  cout << curr_sum + 1;
}
