#pragma once
#include <iostream>
namespace mango {
template <typename T, size_t N> class Array {
public:
  Array() = default;

  constexpr bool empty() const noexcept {
    if (N == 0)
      return true;
    return false;
  }

  constexpr void set_null() noexcept { memset(data_, 0, N * sizeof(T)); }

  constexpr size_t size() const noexcept { return N; }
  constexpr T *data() noexcept { return data_; }

  constexpr const T *data() const noexcept { return data_; }

  constexpr const T &operator[](const size_t &index) const noexcept {
    return data_[index];
  }
  constexpr T &operator[](const size_t &index) noexcept { return data_[index]; }

private:
  T data_[N];
};

static void RunArrayTest() {
  std::cout << "\n----------------------\nArrays:\n";
  Array<int, 2> array{};
  std::cout << "array.empty() " << array.empty() << "\n";
  array.set_null();
  std::cout << "All array elements are set to 0\n";
  for (size_t i = 0; i < array.size(); ++i)
    std::cout << "Array element " << i << " = " << array[i] << "\n";

  array[0] = 2;
  array[1] = 2;
  std::cout << "All array elements are set to 2\n";
  for (size_t i = 0; i < array.size(); ++i)
    std::cout << "Array element " << i << " = " << array[i] << "\n";
}
} // namespace mango
