#include <iostream>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

constexpr ll mod = 1e9 + 7;
ll dp[1000][1000] = {{0}};

int main() {
  ll n;
  cin >> n;

  char grid[1000][1000];
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++)
      cin >> grid[i][j];

  // if we can't get to lower-right, return 0;
  if (grid[n - 1][n - 1] == '*' || grid[0][0] == '*') {
    cout << 0;
    return 0;
  }

  dp[0][0] = 1;

  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      if (grid[i][j] == '.') {
        if (i > 0) {
          dp[i][j] += dp[i - 1][j];
        }
        if (j > 0) {
          dp[i][j] += dp[i][j - 1];
        }
        dp[i][j] %= mod;
      }
    }
  }

  cout << dp[n - 1][n - 1];
}
