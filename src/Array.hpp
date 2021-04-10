#ifndef ARRAY_HPP
#define ARRAY_HPP
namespace mango {
template <typename T, size_t N> class Array {
public:
  Array() = default;

  constexpr bool empty() { return N == 0; }
  constexpr size_t size() noexcept { return N; }
  constexpr T *data() noexcept { return data_; }
  [[nodiscard]] constexpr const T *data() const noexcept { return data_; }
  constexpr const T &operator[](const size_t &index) const noexcept {
    return data_[index];
  }
  constexpr T &operator[](const size_t &index) noexcept { return data_[index]; }

private:
  T data_[N];
};
} // namespace mango
#endif // ARRAY_HPP
