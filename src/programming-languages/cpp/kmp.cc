#include <iostream>
#include <string>
#include <vector>
using namespace std;

int kmp(const string &t, const string &p) {
  if (p.empty()) {
    return 0;
  }

  vector<int> pi(p.size(), 0);
  for (int i = 1, k = 0; i < p.size(); i++) {
    while (k && p[k] != p[i]) {
      k = pi[k - 1];
    }
    if (p[k] == p[i]) {
      k++;
    }
    pi[i] = k;
  }

  for (int i = 0, k = 0; i < t.size(); i++) {
    while (k && p[k] != t[i]) {
      k = pi[k - 1];
    }
    if (p[k] == t[i]) {
      k++;
    }
    if (k == p.size()) {
      return i - k + 1;
    }
  }

  return -1;
}

int main() {
  string t = "aaaaaba";
  string p = "aba";
  cout << kmp(t, p) << '\n';
}
