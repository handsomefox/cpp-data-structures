#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <iostream>

namespace mango {
class String {
public:
  String() = default;
  String(const char *str) {
    set_all_params(strlen(str) + 1);
    string_ = alloc(size());
    cpy_str(str, size());
  }
  String(String &&other) noexcept {
    set_all_params(other.size());
    assign_str(other.string_);
  }
  String(const String &other) {
    set_all_params(other.size());
    string_ = alloc(size());
    cpy_str(other.string_, size());
  }
  ~String() { delete[] string_; }

  void print() const { std::cout << c_str() << "\n"; }

  char &at(const size_t pos) {
    if (length() < pos)
      __debugbreak();
    return string_[pos];
  }

  String &append(const String &str) {
    const auto newSize = str.size() + size();
    auto *const newString = alloc(newSize);

    newString[0] = 0;

    if (string_ != nullptr)
      cpy_str(newString, newSize, string_);

    add_strs(newString, newSize, str.string_);

    assign_str(newString);
    set_all_params(newSize);

    return *this;
  }

  String &append(const String &str, const size_t subpos,
                 const size_t sublen = npos) {
    const auto newSize = str.size() + sublen;
    auto *newString = alloc(newSize);
    newString[0] = 0;

    cpy_str(newString, newSize, string_);

    auto *temp = new char[sublen + 1];
    temp[0] = 0;

    for (auto i = subpos; i < subpos + sublen; ++i)
      temp[i - subpos] = str.at(i);

    temp[sublen] = 0;
    add_strs(newString, newSize, temp);

    delete[] temp;

    assign_str(newString);
    set_all_params(newSize);

    return *this;
  }
  String &append(const char *str) {
    const auto newSize = strlen(str) + size_;
    auto *newString = new char[newSize];
    newString[0] = 0;

    if (string_ != nullptr)
      cpy_str(newString, newSize, string_);

    add_strs(newString, newSize, str);

    assign_str(newString);
    set_all_params(newSize);

    return *this;
  }
  String &append(const char *str, const size_t n) {
    const auto newSize = size_ + n;
    auto *newString = alloc(newSize);
    newString[0] = 0;

    cpy_str(newString, newSize, string_);

    auto *temp = new char[n + 1];
    temp[0] = 0;

    for (size_t i = 0; i < n; ++i)
      temp[i] = str[i];

    temp[n] = 0;
    add_strs(newString, newSize, temp);

    delete[] temp;

    assign_str(newString);
    set_all_params(newSize);

    return *this;
  }
  String &append(const size_t n, const char c) {
    auto *str = new char[n + 1];

    for (size_t i = 0; i < n; ++i)
      str[i] = c;

    str[n] = 0;

    const auto newSize = size_ + n;
    auto *newString = alloc(newSize);
    newString[0] = 0;

    cpy_str(newString, newSize, string_);
    add_strs(newString, newSize, str);

    delete[] str;

    assign_str(newString);
    set_all_params(newSize);

    return *this;
  }

  const char &at(const size_t pos) const {
    if (length_ < pos)
      __debugbreak();
    return string_[pos];
  }

  char &back() {
    if (!empty())
      return string_[length_ - 1];
    else
      __debugbreak();
  }
  char &back() const {
    if (!empty())
      return string_[length_ - 1];
    else
      __debugbreak();
  }
  char &front() const {
    if (!empty())
      return string_[0];
    else
      __debugbreak();
  }
  char &front() {
    if (!empty())
      return string_[0];
    else
      __debugbreak();
  }

  bool empty() const { return length_ == 0; }

  void clear() {
    memset(string_, 0, size_);
    length_ = 0;
  }
  const char *c_str() const noexcept { return string_; }

  size_t capacity() const { return capacity_; }
  size_t capacity() { return capacity_; }

  size_t size() const { return size_; }
  size_t size() { return size_; }

  void shrink_to_fit() {
    if (capacity() == size())
      return;
    auto *newString = alloc(size());
    cpy_str(newString, size(), string_);
    capacity_ = size_;
    assign_str(newString);
  }

  size_t length() const { return length_; }
  size_t length() { return length_; }

  String &operator=(const String &other) {
    if (this == &other)
      return *this;

    set_all_params(other.size());

    auto *newString = alloc(size());
    cpy_str(newString, size_, other.string_);

    assign_str(newString);

    return *this;
  }

  constexpr String &operator=(String &&other) noexcept {
    if (this == &other)
      return *this;

    assign_str(other.string_);
    set_all_params(other.size());

    return *this;
  }

  String &operator=(const char *str) {
    if (this->c_str() == str)
      return *this;

    set_all_params(strlen(str) + 1);
    string_ = alloc(size());
    cpy_str(string_, size(), str);

    return *this;
  }

  bool operator==(const String &other) const {
    return !strcmp(string_, other.string_);
  }
  bool operator==(const char *other) const { return !strcmp(string_, other); }

  String operator+(const String &other) const {
    const auto newSize = length_ + other.length_ + 1;
    auto *newString = alloc(newSize);

    newString[0] = 0;

    cpy_str(newString, newSize, string_);
    add_strs(newString, newSize, other.string_);

    String ret(newString);
    delete[] newString;
    return ret;
  }
  String operator+(const char *other) const {
    const auto newSize = length_ + strlen(other) + 1;
    auto *newString = alloc(newSize);

    newString[0] = 0;

    cpy_str(newString, newSize, string_);
    add_strs(newString, newSize, other);

    String ret(newString);
    delete[] newString;
    return ret;
  }

  friend std::ostream &operator<<(std::ostream &os, const String &str) {
    os << str.string_;
    return os;
  }

  static const size_t npos = -1;
  static size_t max_size() { return SIZE_MAX; }
  void resize(const size_t length) {
    if (length == this->length())
      return;

    const auto newSize = length + 1;
    const auto newLength = length;
    const auto c = ' ';

    auto *newString = alloc(newSize);

    if (newLength < this->length()) {
      for (size_t i = 0; i < newSize; ++i)
        newString[i] = string_[i];
    } else {
      for (size_t i = 0; i < this->length(); ++i)
        newString[i] = string_[i];

      for (auto i = this->length(); i < newLength; ++i)
        newString[i] = c;
    }

    set_all_params(newSize);
    newString[newSize - 1] = '\0';

    assign_str(newString);
  }
  void resize(const size_t length, const char c) {
    if (length == this->length())
      return;

    const auto newSize = length + 1;
    const auto newLength = length;

    auto *newString = alloc(newSize);

    if (newLength < this->length()) {
      for (size_t i = 0; i < newSize; ++i)
        newString[i] = string_[i];
    } else {
      for (size_t i = 0; i < this->length(); ++i)
        newString[i] = string_[i];

      for (auto i = this->length(); i < newLength; ++i)
        newString[i] = c;
    }

    set_all_params(newSize);
    newString[newSize - 1] = '\0';

    assign_str(newString);
  }

  void reserve(const size_t capacity = 0) {
    auto *newString = alloc(capacity);
    cpy_str(newString, capacity, string_);
    capacity_ = capacity;
    assign_str(newString);
  }

private:
  char *string_ = nullptr;
  size_t size_{0};
  size_t length_{0};
  size_t capacity_{0};

  void assign_str(char *string) {
    delete[] string_;
    string_ = string;
  }
  static char *alloc(const size_t size) { return new char[size]; }
  char *get_str() const { return string_; }
  char *get_str() { return string_; }
  void cpy_str(const char *other, const size_t buffer_size) const {
    strcpy_s(string_, buffer_size, other);
  }
  void cpy_str(char *dest, const size_t buffer_size, const char *other) const {
    strcpy_s(dest, buffer_size, other);
  }

  void add_strs(char *dest, const size_t buffer_size, const char *other) const {
    strcat_s(dest, buffer_size, other);
  }
  void set_all_params(const size_t size) {
    size_ = size;
    length_ = size - 1;
    capacity_ = size;
  }
};
} // namespace mango
#endif // STRING_HPP
