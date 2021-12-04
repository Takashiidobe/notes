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

  for (const auto coin : coins)
    dp[coin] = 1;

  for (int i = 1; i <= x; i++) {
    for (const auto coin : coins) {
      if (i - coin > 0) {
        dp[i] = (dp[i] + dp[i - coin]) % mod;
      }
    }
  }

  cout << dp[x] << ' ';
}
