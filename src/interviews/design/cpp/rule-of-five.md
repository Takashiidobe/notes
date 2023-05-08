# What is the rule of 5?

The rule of five stipulates that any constructible, copyable, and movable type that manages a resource should have the following five member functions declared:

1. A destructor to free the resource
2. A copy constructor to copy the resource
3. A move constructor to copy the resource
4. A copy assignment operator to free the left hand resource and copy the right hand one.
5. A move assignment operator to free the left hand resource and transfer ownership of the right hand one.

The fourth and fifth parts can be combined to one by-value assignment operator to free the left hand side and transfer ownership of the right hand one.

```cpp
class Vec {
  std::unique_ptr<int[]> uptr_;
  int size_;
public:
  ~Vec() = default; // 1. Destroy
  Vec(const Vec& rhs) { // 2. Copy constructor
    using std::copy;
    uptr_ = std::make_unique<int[]>(rhs.size_);
    size_ = rhs.size_;
    copy(rhs.ptr_, rhs.ptr + size_, ptr_);
  }
  Vec(vec&& rhs) noexcept = default; // 3. Move constructor
  friend void swap(Vec& a, Vec& b) noexcept {
    a.swap(b);
  }
  Vec& operator=(Vec copy) { // 4. by value assignment operator
    copy.swap(*this);
    return *this;
  }
  void swap(Vec& rhs) noexcept {
    using std::swap;
    swap(uptr_, rhs.uptr_);
    swap(size_, rhs.size_);
  }
};
```
