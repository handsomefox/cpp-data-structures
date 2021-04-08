#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <iostream>

namespace mango {
class String {
public:
  String() { reserve(24); }

  String(const char *str) {
    set_str_props(strlen(str) + 1);
    alloc(size());
    strcpy_s(string_, size(), str);
  }

  String(const String &other) {
    set_str_props(other.size());
    alloc(size());
    strcpy_s(string_, size(), other.string_);
  }

  String(String &&other) noexcept {
    set_str_props(other.size());
    strmove(other.string_);
  }

  ~String() { delete[] string_; }

  char &at(const size_t pos) {
    if (length() < pos)
      __debugbreak();
    return string_[pos];
  }

  String &append(const String &str) {
    const auto tmp_size = str.size() + size();
    realloc(tmp_size);

    strcat_s(string_, tmp_size, str.string_);
    set_str_props(tmp_size);

    return *this;
  }
  String &append(const char *str) {
    const auto tmp_size = strlen(str) + size();
    realloc(tmp_size);

    strcat_s(string_, tmp_size, str);
    set_str_props(tmp_size);

    return *this;
  }

  String &append(const String &str, const size_t subpos,
                 const size_t sublen = npos) {
    const auto tmp_size = str.size() + sublen;
    realloc(tmp_size);

    auto *tmp_str = new char[sublen + 1];
    tmp_str[0] = 0;

    for (auto i = subpos; i < subpos + sublen; ++i)
      tmp_str[i - subpos] = str.at(i);

    tmp_str[sublen] = 0;

    strcat_s(string_, tmp_size, tmp_str);
    set_str_props(tmp_size);

    delete[] tmp_str;
    return *this;
  }
  String &append(const char *str, const size_t n) {
    const auto tmp_size = size_ + n;
    realloc(tmp_size);

    auto *tmp_str = new char[n + 1];
    tmp_str[0] = 0;

    for (size_t i = 0; i < n; ++i)
      tmp_str[i] = str[i];

    tmp_str[n] = 0;

    strcat_s(string_, tmp_size, tmp_str);
    set_str_props(tmp_size);

    delete[] tmp_str;
    return *this;
  }
  String &append(const size_t n, const char c) {
    auto *tmp_str = new char[n + 1];

    for (size_t i = 0; i < n; ++i)
      tmp_str[i] = c;

    tmp_str[n] = 0;

    const auto tmp_size = size_ + n;
    realloc(tmp_size);

    strcat_s(string_, tmp_size, tmp_str);
    set_str_props(tmp_size);

    delete[] tmp_str;
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
      return string_[npos];
  }
  char &back() const {
    if (!empty())
      return string_[length_ - 1];
    return string_[npos];
  }
  char &front() const {
    if (!empty())
      return string_[0];
    return string_[npos];
  }
  char &front() {
    if (!empty())
      return string_[0];
    return string_[npos];
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
    alloc(size());
    capacity_ = size_;
  }

  size_t length() const { return length_; }
  size_t length() { return length_; }

  String &operator=(const String &other) {
    if (this == &other)
      return *this;

    set_str_props(other.size());
    realloc(size());
    strcpy_s(string_, size(), other.string_);

    return *this;
  }
  String &operator=(const char *str) {
    if (this->c_str() == str)
      return *this;

    set_str_props(strlen(str) + 1);
    realloc(size());
    strcpy_s(string_, capacity_, str);

    return *this;
  }

  constexpr String &operator=(String &&other) noexcept {
    if (this == &other)
      return *this;

    set_str_props(other.size());
    strmove(other.string_);

    return *this;
  }

  bool operator==(const String &other) const {
    return !strcmp(string_, other.string_);
  }
  bool operator==(const char *other) const { return !strcmp(string_, other); }

  String operator+(const String &other) const {
    const auto tmp_size = size() + other.length();
    auto *tmp_str = new char[tmp_size];
    tmp_str[0] = 0;

    strcpy_s(tmp_str, tmp_size, string_);
    strcat_s(tmp_str, tmp_size, other.string_);

    String ret(tmp_str);
    delete[] tmp_str;
    return ret;
  }
  String operator+(const char *other) const {
    const auto tmp_size = size() + strlen(other);
    auto *tmp_str = new char[tmp_size];
    tmp_str[0] = 0;

    strcpy_s(tmp_str, tmp_size, string_);
    strcat_s(tmp_str, tmp_size, other);

    String ret(tmp_str);
    delete[] tmp_str;
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

    const auto tmp_size = length + 1;
    const auto tmp_length = length;
    const auto c = ' ';

    auto *tmp_str = new char[tmp_size];

    if (tmp_length < this->length()) {
      for (size_t i = 0; i < tmp_size; ++i)
        tmp_str[i] = string_[i];
    } else {
      for (size_t i = 0; i < this->length(); ++i)
        tmp_str[i] = string_[i];

      for (auto i = this->length(); i < tmp_length; ++i)
        tmp_str[i] = c;
    }

    set_str_props(tmp_size);
    tmp_str[tmp_size - 1] = '\0';
    strmove(tmp_str);
  }
  void resize(const size_t length, const char c) {
    if (length == this->length())
      return;

    const auto tmp_size = length + 1;
    const auto tmp_length = length;

    auto *tmp_str = new char[tmp_size];

    if (tmp_length < this->length()) {
      for (size_t i = 0; i < tmp_size; ++i)
        tmp_str[i] = string_[i];
    } else {
      for (size_t i = 0; i < this->length(); ++i)
        tmp_str[i] = string_[i];

      for (auto i = this->length(); i < tmp_length; ++i)
        tmp_str[i] = c;
    }

    set_str_props(tmp_size);
    tmp_str[tmp_size - 1] = '\0';

    strmove(tmp_str);
  }

  void reserve(const size_t capacity = 0) {
    realloc(capacity);
    capacity_ = capacity;
  }

  void push_back(const char c) { append(1, c); }

  // size_t find(const String &str, size_t pos = 0) const noexcept {}
  // size_t find(const char *s, size_t pos = 0) const {}
  // size_t find(const char *s, size_t pos, size_t n) const {}
  // size_t find(char c, size_t pos = 0) const noexcept {}

private:
  char *string_ = nullptr;
  size_t size_{0};
  size_t length_{0};
  size_t capacity_{0};

  void strmove(char *string) {
    delete[] string_;
    string_ = string;
  }
  void alloc(const size_t size) {
    if (string_ == nullptr) {
      string_ = new char[size];
      string_[0] = 0;
    } else if (capacity_ < size_) {
      auto *tmp_str = new char[size];
      tmp_str[0] = 0;
      strcpy_s(tmp_str, size, string_);
      delete[] string_;
      string_ = tmp_str;
    }
  }
  void realloc(const size_t size) {
    if (capacity_ < size) {
      auto *mem = new char[size];
      mem[0] = 0;
      if (string_ != nullptr)
        strcpy_s(mem, size, string_);
      delete[] string_;
      string_ = mem;
    }
  }
  void set_str_props(const size_t size) {
    size_ = size;
    length_ = size - 1;
    if (capacity_ < size_) {
      capacity_ = size_;
    }
  }
};
} // namespace mango
#endif // STRING_HPP
