#include "array.cc"
#include "util.h"

template <class T> class ArrayStack {
private:
  Arr<T> a;
  size_t _size = 0;

public:
  size_t size() { return _size; }
  T get(size_t i) { return a[i]; }
  T set(size_t i, T item) {
    T y = a[i];
    a[i] = item;
    return y;
  }
  void resize() {
    Arr<T> b(max(2 * _size, 1));
    for (int i = 0; i < _size; i++)
      b[i] = a[i];
    a = b;
    _size *= 2;
  }
  void add(int i, T x) {
    if (_size + 1 > a.length)
      resize();
    for (int j = _size; j > i; j--)
      a[j] = a[j - 1];
    a[i] = x;
    _size++;
  }
};

int main() {}
