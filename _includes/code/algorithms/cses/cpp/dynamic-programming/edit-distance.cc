#include <iostream>
#include <string>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

int main() {
  string l, r;
  cin >> l >> r;

  vector<vector<int>> dp(l.size() + 1, vector<int>(r.size() + 1, 0));

  for (int i = 0; i <= l.size(); i++) {
    for (int j = 0; j <= r.size(); j++) {
      if (i == 0 && j == 0) {
        continue;
      } else if (i == 0) {
        dp[i][j] = j;
      } else if (j == 0) {
        dp[i][j] = i;
      } else if (l[i - 1] == r[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        int left_above = dp[i - 1][j - 1];
        int above = dp[i - 1][j];
        int left = dp[i][j - 1];
        dp[i][j] = 1 + min({left_above, above, left});
      }
    }
  }

  for (int i = 0; i < l.size(); i++) {
    for (int j = 0; j < r.size(); j++) {
      cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }

  cout << dp[l.size()][r.size()];
}
