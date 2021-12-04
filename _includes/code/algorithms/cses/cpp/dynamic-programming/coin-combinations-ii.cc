#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

constexpr ll mod = 1e9 + 7;
ll dp[1000001] = {0};

int main() {
  ll n, x;
  cin >> n >> x;

  vector<int> coins(n);

  for (int i = 0; i < n; i++)
    cin >> coins[i];

  dp[0] = 1;

  for (const auto coin : coins) {
    for (int i = 1; i <= x; i++) {
      if (i - coin >= 0) {
        dp[i] += dp[i - coin];
        dp[i] %= mod;
      }
    }
  }

  cout << dp[x];
}
