#pragma once
#include <iostream>

namespace mango {
template <typename T> class Vector {
public:
  Vector() { reserve(2); }

  explicit Vector(const size_t capacity) { reserve(capacity); }

  Vector(const Vector &vec) {
    size_ = vec.size_;
    capacity_ = vec.capacity_;

    data_ = new T[sizeof &vec.data_];
    memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);
  }

  Vector(Vector &&vec) noexcept {
    size_ = vec.size_;
    capacity_ = vec.capacity_;
    data_ = std::move(vec.data_);
  }

  ~Vector() { delete[] data_; }

  T &front() { return data_[0]; }

  T &back() { return data_[size_ - 1]; }

  T *data() { return data_; }

  void reserve(const size_t new_capacity) {
    capacity_ += new_capacity;
    T *newData = new T[capacity_];

    for (size_t i = 0; i < size_; ++i)
      newData[i] = data_[i];

    delete[] data_;
    data_ = newData;
  }

  bool empty() const { return size_ == 0 ? true : false; }

  size_t size() { return size_; }
  size_t size() const { return size_; }

  size_t capacity() { return capacity_; }
  size_t capacity() const { return capacity_; }

  void clear() {
    for (size_t i = 0; i < size_; ++i)
      data_[i].~T();
    size_ = 0;
  }

  void push_back(T data) {
    if (size_ >= capacity_)
      reserve(capacity_ + capacity_ / 2);

    data_[size_++] = data;
  }

  template <typename... Args> T &emplace_back(Args &&...args) {
    if (size_ >= capacity_)
      reserve(capacity_ + capacity_ / 2);

    data_[size_] = T(std::forward<Args>(args)...);
    return data_[size_++];
  }

  void pop_back() {
    if (size_ > 0) {
      size_--;
      data_[size_].~T();
    }
  }

  void resize(const size_t size) {
    T *newData = new T[size];

    for (size_t i = 0; i < size; ++i) {
      if (i < size_)
        newData[i] = data_[i];
      else if (std::is_integral_v<T>)
        newData[i] = static_cast<T>(0);
    }
    delete[] data_;

    size_ = size;
    capacity_ = size;
    data_ = newData;
  }

  void print() {
    std::cout << "Printing Vector: \n";
    for (size_t i = 0; i < size_; ++i)
      std::cout << data_[i] << "\n";
  }

  const T &operator[](size_t index) const { return data_[index]; }

  constexpr T &operator[](size_t index) { return data_[index]; }

  constexpr Vector &operator=(const Vector &vec) {
    if (this == &vec)
      return *this;

    this->size_ = vec.size_;
    this->capacity_ = vec.capacity_;

    data_ = new T[sizeof &vec.data_];
    memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);

    return *this;
  }

  constexpr Vector &operator=(Vector &&vec) noexcept {
    if (this == &vec)
      return *this;

    size_ = vec.size_;
    capacity_ = vec.capacity_;

    data_ = vec.data_;

    return *this;
  }

private:
  T *data_ = nullptr;

  size_t size_ = 0;
  size_t capacity_ = 0;
};

static void RunVectorTest() {
  std::cout << "Vector test:\n";
  Vector<int> vec;
  vec.print();
  std::cout << "Empty: " << vec.empty() << "\n";
  vec.reserve(100);
  std::cout << "Adding data to Vector\n";
  vec.push_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  vec.emplace_back(4);
  vec.print();

  std::cout << "Empty: " << vec.empty() << "\n";

  std::cout << "Back: " << vec.back() << "\n";
  std::cout << "Front: " << vec.front() << "\n";
  std::cout << "Capacity: " << vec.capacity() << "\n";
  std::cout << "Size: " << vec.size() << "\n";

  std::cout << "Pop back\n";
  vec.pop_back();
  vec.print();

  std::cout << "Resize (smaller)\n";
  vec.resize(2);
  vec.print();

  std::cout << "Resize (bigger)\n";
  vec.resize(5);
  vec.print();

  std::cout << "Clear\n";
  vec.clear();

  std::cout << "Print (expected == nothing)\n";
  vec.print();

  std::cout << "Constructing a Vector with capacity of 5\n";
  Vector<std::string> vec2(5);
  std::cout << "Capacity: " << vec2.capacity() << "\n";
  std::cout << "Empty: " << vec2.empty() << "\n";
  std::cout << "Size: " << vec2.size() << "\n";

  std::cout << "Adding data to Vector\n";
  vec2.push_back("Hello");
  vec2.push_back("this");
  vec2.push_back("is");
  vec2.push_back("my Vector!");
  vec2.print();

  std::cout << "Capacity: " << vec2.capacity() << "\n";
  std::cout << "Empty: " << vec2.empty() << "\n";
  std::cout << "Size: " << vec2.size() << "\n";

  std::cout << "Back: " << vec2.back() << "\n";
  std::cout << "Front: " << vec2.front() << "\n";

  std::cout << "Pop back\n";
  vec2.pop_back();
  vec2.print();

  std::cout << "Resize (smaller)\n";
  vec2.resize(1);
  vec2.print();

  std::cout << "Resize (bigger)\n";
  vec2.resize(5);
  vec2.print();

  std::cout << "Clear\n";
  vec2.clear();

  std::cout << "Print (expected == nothing)\n";
  vec2.print();

  Vector<int> vec3;
  vec3[0] = 2;
  auto vec4 = vec3;
  std::cout << "vec3[0]: " << vec3[0] << "\n";
  std::cout << "vec4[0]: " << vec4[0] << "\n";
}
} // namespace mango
