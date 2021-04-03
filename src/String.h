#pragma once
#include <iostream>

#include <cstring>

namespace mango {
class String {
public:
  String() = default;
  explicit String(const char *str) {
    string_ = new char[strlen(str) + 1];
    strcpy_s(string_, strlen(str) + 1, str);
    length_ = strlen(str);
    size_ = length_ + 1;
  }
  String(String &&str) noexcept {
    string_ = str.string_;
    size_ = str.size_;
    length_ = str.length_;
  }
  String(const String &str) {
    string_ = new char[str.size_];
    strcpy_s(string_, str.size_, str.string_);
    size_ = str.size_;
    length_ = str.length_;
  }
  ~String() { delete[] string_; }

  void print() const {
    std::cout << "Printing a string...\n";
    std::cout << string_ << "\n";
  }

  const char *c_str() const noexcept { return string_; }

  size_t size() const { return size_; }
  size_t size() { return size_; }

  size_t length() const { return length_; }
  size_t length() { return length_; }

  constexpr String &operator=(const String &str) {
    if (this == &str)
      return *this;

    delete[] string_;

    string_ = str.string_;
    size_ = str.size_;
    length_ = str.length_;

    return *this;
  }

  constexpr String &operator=(String &&str) noexcept {
    if (this == &str)
      return *this;

    delete[] string_;

    string_ = str.string_;
    size_ = str.size_;
    length_ = str.length_;

    return *this;
  }

  bool operator==(const String &other) const {
    return !strcmp(string_, other.string_);
  }
  bool operator==(const char *other) const { return !strcmp(string_, other); }

  String operator+(const String &other) const
  {
	auto* ret = new String;
    ret->size_ = this->length_ + other.length_ + 1;
    ret->length_ = ret->size_ -1;

    auto *new_string = new char[ret->size_];
    new_string[0] = 0;

    strcpy_s(new_string, ret->size_, this->string_);
    strcat_s(new_string, ret->size_, other.string_);

    ret->string_ = new_string;
    return *ret;
  }
  String operator+(const char* other) const
  {
      auto* ret = new String;
      ret->size_ = this->length_ + strlen(other) + 1;
      ret->length_ = ret->size_ - 1;

      auto* new_string = new char[ret->size_];
      new_string[0] = 0;

      strcpy_s(new_string, ret->size_, this->string_);
      strcat_s(new_string, ret->size_, other);

      ret->string_ = new_string;
      return *ret;
  }

  friend std::ostream &operator<<(std::ostream &stream, const String &str) {
    stream << str.string_;
    return stream;
  }

private:
  char *string_ = nullptr;
  size_t size_{0};
  size_t length_{0};
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
