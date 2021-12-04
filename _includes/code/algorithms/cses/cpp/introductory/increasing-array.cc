#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  vector<ll> v(n);
  int moves = 0;

  for (int i = 0; i < n; i++)
    cin >> v[i];

  int i = 0;
  int j = 1;

  while (j < n) {
    if (v[i] > v[j]) {
      moves += (v[i] - v[j]);
    }
    i++;
    j++;
  }

  cout << moves;
}
