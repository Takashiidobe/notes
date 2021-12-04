#include <iostream>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string s;
  cin >> s;

  int ans = 1;
  int curr = 0;
  char l = 'A';
  for (char c : s) {
    if (c == l) {
      curr++;
      ans = max(ans, curr);
    } else {
      l = c;
      curr = 1;
    }
  }
  cout << ans;
}
