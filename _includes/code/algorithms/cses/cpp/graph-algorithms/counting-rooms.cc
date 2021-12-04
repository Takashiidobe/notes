#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

void bfs(vector<vector<char>> &grid, int i, int j, int n, int m) {
  if (i < 0 || j < 0 || i == n || j == m) {
    return;
  } else if (grid[i][j] == '#') {
    return;
  }

  grid[i][j] = '#';
  bfs(grid, i + 1, j, n, m);
  bfs(grid, i - 1, j, n, m);
  bfs(grid, i, j - 1, n, m);
  bfs(grid, i, j + 1, n, m);
}

int main() {
  int n, m;
  cin >> n >> m;

  int ans = 0;

  vector<vector<char>> grid(n + 1, vector<char>(m + 1));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '.') {
        ans++;
        bfs(grid, i, j, n, m);
      }
    }
  }

  cout << ans;
}
