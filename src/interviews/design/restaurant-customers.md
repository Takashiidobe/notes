# Restaurant Customers

## Prompt

You are given the arrival and leaving times of n customers in a restaurant.

What was the maximum number of customers in the restaurant at any time?

Input

Each tuple in customers has an arrival time and a leaving time.

You may assume that all arrival and leaving times are distinct.

Output

Print one integer: the maximum number of customers.

## Solution

```python
def max_customers(customers: List[(int, int)]) -> int:
  customers.sort()
  q = []

  for enter_time, leave_time in customers:
    q.append((enter_time, True))
    q.append((leave_time, False))

  customers = 0
  max_customers_so_far = 0

  for _, status in q:
    customers += (1 if status else -1)
    max_customers_so_far = max(max_customers_so_far, customers)

  return max_customers_so_far
```

```cpp
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

int main() {
  long long n;
  long long enter_time;
  long long leaving_time;
  cin >> n;

  vector<pair<int, bool>> q;

  for (int i = 0; i < n; i++) {
    cin >> enter_time;
    cin >> leaving_time;
    q.push_back({enter_time, true});
    q.push_back({leaving_time, false});
  }

  sort(q.begin(), q.end());

  long long customers = 0;
  long long max_customers_so_far = 0;

  for (const auto &[l, r] : q) {
    if (r == true)
      customers++;
    else
      customers--;

    max_customers_so_far = max(max_customers_so_far, customers);
  }

  cout << max_customers_so_far;
}
```
