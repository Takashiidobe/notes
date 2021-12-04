#include "util.h"

template <class T> class Array {
private:
  T *array = new T[8]{};
  size_t capacity = 8;

public:
  Array() = default;
  Array(size_t size) {
    capacity = size;
    array = new T[size]{};
  }
  ~Array() { delete[] array; }
  size_t size() { return capacity; }
  const T *begin() const { return &array[0]; }
  const T *end() const { return &array[capacity]; }
  T &operator[](const size_t index) {
    assert(index >= 0 && index < capacity);
    return array[index];
  }
};

int main() {
  auto arr = Array<int>{2};
  arr[0] = 1;
  arr[1] = 2;
  for (const auto item : arr) {
    _print(item);
  }
}
