#include <array>
#include <iostream>

using namespace std;

constexpr int N = 7;
array<array<bool, N>, N> visited{};
int paths = 0;

inline bool is_inbounds(const int i, const int j) {
  return i >= 0 && j >= 0 && i < N && j < N && !visited[i][j];
}

inline bool is_solvable(const int i, const int j) {
  bool is_first_row = i == 0;
  bool is_last_row = i + 1 == N;
  bool is_first_col = j == 0;
  bool is_last_col = j + 1 == N;
  bool visited_prev_row = visited[i - 1][j];
  bool visited_next_row = visited[i + 1][j];
  bool visited_prev_col = visited[i][j - 1];
  bool visited_next_col = visited[i][j + 1];

  bool first =
      ((is_last_row || (visited_prev_row && visited_next_row)) &&
       !is_first_col && !is_last_col && !visited_prev_col && !visited_next_col);

  bool second =
      ((is_last_col || (visited_prev_col && visited_next_col)) &&
       !is_first_row && !is_last_row && !visited_prev_row && !visited_next_row);

  bool third =
      ((is_first_row || (visited_next_row && visited_prev_row)) &&
       !is_first_col && !is_last_col && !visited_prev_col && !visited_next_col);

  bool fourth =
      ((is_first_col || (visited_next_col && visited_prev_col)) &&
       !is_first_row && !is_last_row && !visited_prev_row && !visited_next_row);

  return !(first || second || third || fourth);
}

void search(const string &s, const int pos = 0, const int i = 0,
            const int j = 0) {

  if (!is_inbounds(i, j))
    return;

  if (i == N - 1 && j == 0) {
    paths += (pos == N * N - 1);
    return;
  }

  if (!is_solvable(i, j))
    return;

  visited[i][j] = true;

  if (s[pos] == 'U') {
    search(s, pos + 1, i - 1, j);
  } else if (s[pos] == 'D') {
    search(s, pos + 1, i + 1, j);
  } else if (s[pos] == 'L') {
    search(s, pos + 1, i, j - 1);
  } else if (s[pos] == 'R') {
    search(s, pos + 1, i, j + 1);
  } else {
    search(s, pos + 1, i, j - 1);
    search(s, pos + 1, i, j + 1);
    search(s, pos + 1, i - 1, j);
    search(s, pos + 1, i + 1, j);
  }

  visited[i][j] = false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s;
  cin >> s;
  search(s);
  cout << paths;
}
