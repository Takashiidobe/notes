#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  int n, x;
  cin >> n >> x;

  vector<int> prices(n);
  vector<int> pages(n);

  for (int &v : prices)
    cin >> v;

  for (int &v : pages)
    cin >> v;

  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= x; j++) {
      dp[i][j] = dp[i - 1][j];
      int money_left = j - prices[i - 1];
      if (money_left >= 0) {
        dp[i][j] = max(dp[i][j], dp[i - 1][money_left] + pages[i - 1]);
      }
    }
  }

  cout << dp[n][x];
}
