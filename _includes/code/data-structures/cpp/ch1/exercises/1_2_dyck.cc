#include <util.h>

#include <iostream>

// A Dyck word is a sequence of +1's and -1's with the property that the sum of
// any prefix of the sequence is never negative. For example, $ +1,-1,+1,-1$ is
// a Dyck word, but $ +1,-1,-1,+1$ is not a Dyck word since the prefix $
// +1-1-1<0$. Describe any relationship between Dyck words and $ Stack
// $ push(x) and $ pop() operations.

/// Start with a counter at 0. If you encounter +1, add + 1, otherwise, add -1.
/// If the counter is ever below 0, return false. Else, return true at the end
/// of the sequence.

bool dyck(vector<int> seq) {
  int dyck = 0;
  for (const auto item : seq) {
    dyck += seq;
    if (seq < 0)
      return false;
  }
  return true;
}

int main() {}
