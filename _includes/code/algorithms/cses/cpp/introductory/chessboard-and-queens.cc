#include <array>
#include <iostream>

using namespace std;

using ll = long long;

#ifndef ONLINE_JUDGE
auto _ = freopen("input.txt", "r", stdin);
#endif

array<bool, 8> col;
array<bool, 15> d1;
array<bool, 15> d2;

void search(int y, int n, int &count, const array<string, 8> &arr) {
  if (y == n) {
    count++;
    return;
  }
  for (int x = 0; x < n; x++) {
    if (col[x] || d1[x + y] || d2[x - y + n - 1] || arr[y][x] == '*')
      continue;
    col[x] = d1[x + y] = d2[x - y + n - 1] = true;
    search(y + 1, n, count, arr);
    col[x] = d1[x + y] = d2[x - y + n - 1] = false;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n = 8;

  array<string, 8> arr;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  int count = 0;

  search(0, n, count, arr);

  cout << count;
}
