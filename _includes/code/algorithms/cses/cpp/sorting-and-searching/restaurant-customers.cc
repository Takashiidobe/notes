#include <functional>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  ll enter_time;
  ll leaving_time;
  cin >> n;

  vector<pair<int, bool>> q;

  for (int i = 0; i < n; i++) {
    cin >> enter_time;
    cin >> leaving_time;
    q.push_back({enter_time, true});
    q.push_back({leaving_time, false});
  }

  sort(q.begin(), q.end());

  ll customers = 0;
  ll max_customers_so_far = 0;

  for (const auto &[_, r] : q) {
    r == true ? customers++ : customers--;

    max_customers_so_far = max(max_customers_so_far, customers);
  }

  cout << max_customers_so_far;
}
