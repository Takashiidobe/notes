#include <unordered_map>
// just use a hashmap?
#include "util.h"

template <class T> class Bag {
private:
  unordered_map<T, vector<T>> m;

public:
  Bag() = default;
  void add(T item) {
    if (m.contains(item)) {
      m[item].push_back(item);
    } else {
      m[item] = {item};
    }
  }
  T remove(T item) {
    if (m.contains(item)) {
      if (m[item].size()) {
        T result = m[item].front();
        m[item].pop_back();
        return result;
      } else {
        throw "Not Found";
      }
    } else {
      throw "Not Found";
    }
  }
  vector<T> findAll(T item) {
    if (m.contains(item)) {
      return m[item];
    } else {
      throw "Not found";
    }
  }
};

int main() {
  Bag<int> b;
  b.add(10);
  b.add(20);
  b.add(30);
  b.add(10);
  b.add(20);
  for (const auto item : b.findAll(10)) {
    _print(item);
  }
}
