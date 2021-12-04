#include "util.h"

template <class T> struct Arr {
  T *a;
  size_t length;
  Arr(size_t _length) {
    length = _length;
    a = new T[_length];
  }

  T &operator[](size_t i) {
    assert(i >= 0 && i < length);
    return a[i];
  }

  Arr<T> &operator=(Arr<T> &b) {
    if (a != nullptr)
      delete[] a;
    a = b.a;
    b.a = nullptr;
    length = b.length;
    return *this;
  }
};
