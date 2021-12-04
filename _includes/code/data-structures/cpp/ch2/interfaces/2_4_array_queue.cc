#include "array.cc"
#include "util.h"

template <class T> class ArrayQueue : Arr<T> {
  Arr<T> a;
  int j;
  int n;

public:
  bool add(T x) {
    if (n + 1 > a.length)
      resize();
    a[(j + n) % a.length] = x;
    n++;
    return true;
  }
  T remove() {
    T x = a[j];
    j = (j + 1) % a.length;
    n--;
    if (a.length >= 3 * n)
      resize();
    return x;
  }
  void resize() {
    Arr<T> b(max(1, 2 * n));
    for (int k = 0; k < n; k++)
      b[k] = a[(j + k) % a.length];
    a = b;
    j = 0;
  }
};
