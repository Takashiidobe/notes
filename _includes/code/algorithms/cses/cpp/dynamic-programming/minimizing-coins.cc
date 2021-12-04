#include <climits>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

vector<ll> dp(1000001, INT_MAX);

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> coins(n);

  for (int i = 0; i < n; i++) {
    cin >> coins[i];
  }

  dp[0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int weight = 0; weight <= x; weight++) {
      if (weight - coins[i - 1] >= 0) {
        dp[weight] = min(dp[weight], dp[weight - coins[i - 1]] + 1);
      }
    }
  }

  cout << (dp[x] == INT_MAX ? -1 : dp[x]);
}
