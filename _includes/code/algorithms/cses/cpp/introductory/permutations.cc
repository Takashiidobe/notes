#include <iostream>
using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  if (n == 1) {
    cout << 1;
    return;
  }
  if (n == 2 || n == 3) {
    cout << "NO SOLUTION";
    return;
  }
  for (int i = 2; i <= n; i += 2) cout << i << " ";
  for (int i = 1; i <= n; i += 2) cout << i << " ";
}
