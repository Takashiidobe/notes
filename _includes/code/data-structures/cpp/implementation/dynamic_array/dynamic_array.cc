#include "util.h"

template <class T> class Array {
private:
  size_t capacity = 8;
  T *array = new T[8]{};
  size_t length = 0;

public:
  Array() = default;
  Array(size_t _capacity);
  ~Array();
  const T *begin() const;
  const T *end() const;
  T &operator[](size_t index) const;
  void push(T value);
  T pop();
};

template <class T> Array<T>::Array(size_t _capacity) {
  capacity = _capacity;
  array = new T[_capacity]{};
}

template <class T> Array<T>::~Array() { delete[] array; }

template <class T> const T *Array<T>::begin() const { return &array[0]; }

template <class T> const T *Array<T>::end() const { return &array[length]; }

template <class T> T &Array<T>::operator[](size_t index) const {
  assert(index >= 0 && index < capacity);
  return array[index];
}

template <class T> void Array<T>::push(T value) {
  if (length == capacity) {
    capacity *= 2;
    T *new_array = new T[capacity];
    for (size_t i = 0; i < length; i++) {
      new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
  }
  array[length] = value;
  length++;
}

template <class T> T Array<T>::pop() {
  assert(length > 0);
  if (length * 2 == capacity) {
    capacity /= 2;
    T *new_array = new T[capacity];
    for (int i = 0; i < length; i++) {
      new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
  }
  length--;
  return array[length];
};

int main() {
  auto arr = Array<int>{};
  for (int i = 0; i < 10; i++) {
    arr.push((i + 1) * 10);
  }
  for (const auto elem : arr) {
    cout << elem << endl;
  }
}
