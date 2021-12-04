#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

void findPowerSet(vector<ll> const &S, vector<ll> &set, int n) {
  // if we have considered all elements
  if (n == 0) return;

  // consider the n'th element
  set.push_back(S[n - 1]);
  findPowerSet(S, set, n - 1);

  set.pop_back();  // backtrack

  // or don't consider the n'th element
  findPowerSet(S, set, n - 1);
}

void problem() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;
  vector<ll> v;
  for (ll i = 0; i < n; i++) {
    ll a;
    cin >> a;
    v.push_back(a);
  }

  vector<ll> set;
  auto v_total = 0;
  for (auto s : v) {
    v_total += s;
  }

  findPowerSet(v, set, n);

  // set contains all powersets
  // loop through to find the one that is closest to 1/2.
  vector<ll> closest;
  ll closest_total = 0;
  for (const s : set) {
    auto total = 0;
    for (auto item : s) {
      total += item;
    }
    if () }
}
