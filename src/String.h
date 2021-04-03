#pragma once
#include <iostream>

#include <cstring>

namespace mango {
class String {
public:
  String() = default;
  explicit String(const char *str) {
    length_   = strlen(str);
    size_     = length_ + 1;
    string_   = new char[size_];
    strcpy_s(string_, size_, str);
  }
  String(String &&str) noexcept {
    length_   = str.length_;
    size_     = str.size_;
    string_   = str.string_;
  }
  String(const String &str) {
    length_   = str.length_;
    size_     = str.size_;
    string_   = new char[size_];
    strcpy_s(string_, size_, str.string_);
  }
  ~String() { delete[] string_; }

  void print() const { std::cout << string_ << "\n"; }

  const char *c_str() const noexcept { return string_; }

  size_t size() const { return size_; }
  size_t size() { return size_; }

  size_t length() const { return length_; }
  size_t length() { return length_; }

  constexpr String &operator=(const String &other) {
    if (this == &other)
      return *this;

    delete[] string_;

    length_   = other.length_;
    size_     = other.size_;
    string_   = other.string_;

    return *this;
  }

  constexpr String &operator=(String &&other) noexcept {
    if (this == &other)
      return *this;

    delete[] string_;

    string_   = other.string_;
    size_     = other.size_;
    length_   = other.length_;

    return *this;
  }

  bool operator==(const String &other) const {
    return !strcmp(string_, other.string_);
  }
  bool operator==(const char *other) const {
     return !strcmp(string_, other); 
  }

  String operator+(const String &other) const {
    auto* ret = new String;
    ret->size_ = this->length_ + other.length_ + 1;
    ret->length_ = ret->size_ - 1;

    ret->string_ = new char[ret->size_];
    ret->string_[0] = 0;

    strcpy_s(ret->string_, ret->size_, this->string_);
    strcat_s(ret->string_, ret->size_, other.string_);

    return *ret;
  }
  String operator+(const char *other) const {
    auto* ret = new String;
    ret->size_ = this->length_ + strlen(other) + 1;
    ret->length_ = ret->size_ - 1;

    ret->string_ = new char[ret->size_];
    ret->string_[0] = 0;

    strcpy_s(ret->string_, ret->size_, this->string_);
    strcat_s(ret->string_, ret->size_, other);

    return *ret;
  }

  friend std::ostream &operator<<(std::ostream &stream, const String &str) {
      return stream << str.string_;
  }

private:
  char *string_ = nullptr;
  size_t size_    { 0 };
  size_t length_  { 0 };
};

inline void RunStringTest() {
  std::cout << "String test:\n";

  const String str("Hello");
  String str2("Not Hello");

  std::cout << "str = " << str << '\n';
  std::cout << "Size of the str: " << str.size() << "\n";
  std::cout << "Length of the str: " << str.length() << "\n";

  std::cout << "str2 = " << str2 << '\n';
  std::cout << "Size of the str2: " << str2.size() << "\n";
  std::cout << "Length of the str2: " << str2.length() << "\n";

  std::cout << "Comparing str to str2: " << (str2 == str) << "\n";
  std::cout << "Comparing str to cstring: " << (str == "Hello") << "\n";

  std::cout << "Concatenated string: " << str2 + str << "\n";
  std::cout << "Concatenated string: " << str2 + " " + str << "\n";
  std::cout << "Concatenated string: " << str2 + str << "\n";
  std::cout << "Concatenated string: " << str2 + " " + str << "\n";
  std::cout << "Concatenated string: " << str2 + str << "\n";

  std::cout << "c_str() from str: " << str.c_str() << "\n";
}
} // namespace mango
