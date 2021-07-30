#pragma once

#include <cstring>
#include <iostream>

class String
{
public:
	String();
	String(const char* other);
	String(const String& other);
	String(String&& other) noexcept;
	~String();
	char& at(const size_t pos);
	String& append(const String& str);
	String& append(const char* str);
	String& append(const String& str, const size_t subpos, const size_t sublen = npos);
	String& append(const char* str, const size_t n);
	String& append(const size_t n, const char c);
	const char& at(const size_t pos) const;
	char& back();
	char& back() const;
	char& front() const;
	char& front();
	bool empty() const;
	void clear();
	const char* c_str() const noexcept;
	size_t capacity() const;
	size_t capacity();
	size_t size() const;
	size_t size();
	void shrink_to_fit();
	size_t length() const;
	size_t length();
	String& operator=(const String& other);
	String& operator=(const char* str);
	constexpr String& operator=(String&& other) noexcept;
	char& operator[](const size_t index) const;
	char& operator[](const size_t index);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs) const;
	String operator+(const String& rhs) const;
	String operator+(const char* rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	static const size_t npos = -1;
	static size_t max_size();
	void resize(const size_t length);
	void resize(const size_t length, const char c);
	void reserve(const size_t capacity = 0);
	void push_back(const char c);
	size_t find(const String& str, size_t pos = 0) const noexcept;
	size_t find(const char* s, size_t pos = 0) const;
	size_t find(const char* s, const size_t pos, const size_t n) const;
	size_t find(const char c, const size_t pos = 0) const noexcept;
	String& replace(const size_t pos, const size_t len, const char* substr);
	String& replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen = npos);

private:
	char* string_ = nullptr;
	size_t size_{ 0 };
	size_t length_{ 0 };
	size_t capacity_{ 0 };

	void strmove(char* string);
	static char* create_null_str(const size_t size);
	void alloc(const size_t size);
	void realloc(const size_t size);
	void set_str_props(const size_t size);
};

inline String::String()
{
	reserve(22);
}

inline String::String(const char* other)
{
	set_str_props(strlen(other) + 1);
	alloc(size_);
	strcpy_s(string_, size_, other);
}

inline String::String(const String& other)
{
	set_str_props(other.size_);
	alloc(size_);
	strcpy_s(string_, size_, other.string_);
}

inline String::String(String&& other) noexcept
{
	set_str_props(other.size_);
	strmove(other.string_);
}

inline String::~String()
{
	delete[] string_;
}

inline char& String::at(const size_t pos)
{
	if (length_ < pos)
	{
		__debugbreak();
	}
	return string_[pos];
}

inline String& String::append(const String& str)
{
	const auto tmp_size = str.size_ + size_;
	realloc(tmp_size);

	strcat_s(string_, tmp_size, str.string_);
	set_str_props(tmp_size);

	return *this;
}

inline String& String::append(const char* str)
{
	const auto tmp_size = 1 + strlen(str) + size_;
	realloc(tmp_size);

	strcat_s(string_, tmp_size, str);
	set_str_props(tmp_size);

	return *this;
}

inline String& String::append(const String& str, const size_t subpos, const size_t sublen)
{
	const auto tmp_size = str.size_ + sublen;
	realloc(tmp_size);

	auto* tmp_str = create_null_str(sublen + 1);

	for (auto i = subpos; i < subpos + sublen; ++i)
	{
		tmp_str[i - subpos] = str[i];
	}

	strcat_s(string_, tmp_size, tmp_str);
	set_str_props(tmp_size);

	delete[] tmp_str;
	return *this;
}

inline String& String::append(const char* str, const size_t n)
{
	const auto tmp_size = size_ + n;
	realloc(tmp_size);

	auto* tmp_str = create_null_str(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		tmp_str[i] = str[i];
	}

	strcat_s(string_, tmp_size, tmp_str);
	set_str_props(tmp_size);

	delete[] tmp_str;
	return *this;
}

inline String& String::append(const size_t n, const char c)
{
	auto* tmp_str = create_null_str(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		tmp_str[i] = c;
	}

	const auto tmp_size = size_ + n;
	realloc(tmp_size);

	strcat_s(string_, tmp_size, tmp_str);
	set_str_props(tmp_size);

	delete[] tmp_str;
	return *this;
}

inline const char& String::at(const size_t pos) const
{
	if (length_ < pos)
	{
		__debugbreak();
	}
	return string_[pos];
}

inline char& String::back()
{
	if (!empty())
	{
		return string_[length_ - 1];
	}
	return string_[npos];
}

inline char& String::back() const
{
	if (!empty())
	{
		return string_[length_ - 1];
	}
	return string_[npos];
}

inline char& String::front() const
{
	if (!empty())
	{
		return string_[0];
	}
	return string_[npos];
}

inline char& String::front()
{
	if (!empty())
	{
		return string_[0];
	}
	return string_[npos];
}

inline bool String::empty() const
{
	return length_ == 0;
}

inline void String::clear()
{
	memset(string_, 0, size_);
	length_ = 0;
}

inline const char* String::c_str() const noexcept
{
	return string_;
}

inline size_t String::capacity() const
{
	return capacity_;
}

inline size_t String::capacity()
{
	return capacity_;
}

inline size_t String::size() const
{
	return size_;
}

inline size_t String::size()
{
	return size_;
}

inline void String::shrink_to_fit()
{
	if (capacity_ == size_)
	{
		return;
	}
	alloc(size_);
	capacity_ = size_;
}

inline size_t String::length() const
{
	return length_;
}

inline size_t String::length()
{
	return length_;
}

inline String& String::operator=(const String& other)
{
	if (this == &other)
	{
		return *this;
	}

	set_str_props(other.size_);
	realloc(size_);
	strcpy_s(string_, size_, other.string_);

	return *this;
}

inline String& String::operator=(const char* str)
{
	if (string_ == str)
	{
		return *this;
	}

	set_str_props(strlen(str) + 1);
	realloc(size_);
	strcpy_s(string_, capacity_, str);

	return *this;
}

constexpr String& String::operator=(String&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	set_str_props(other.size_);
	strmove(other.string_);

	return *this;
}

inline char& String::operator[](const size_t index) const
{
	return string_[index];
}

inline char& String::operator[](const size_t index)
{
	return string_[index];
}

inline bool String::operator==(const String& rhs) const
{
	return !strcmp(string_, rhs.string_);
}

inline bool String::operator==(const char* rhs) const
{
	return !strcmp(string_, rhs);
}

inline String String::operator+(const String& rhs) const
{
	const auto tmp_size = rhs.size_ + size_;
	auto* tmp_str = create_null_str(tmp_size);

	strcpy_s(tmp_str, tmp_size, string_);
	strcat_s(tmp_str, tmp_size, rhs.string_);

	const auto ret = std::make_unique<String>(tmp_str);
	delete[] tmp_str;
	return *ret;
}

inline String String::operator+(const char* rhs) const
{
	const auto tmp_size = 1 + strlen(rhs) + size_;
	auto* tmp_str = create_null_str(tmp_size);

	strcpy_s(tmp_str, tmp_size, string_);
	strcat_s(tmp_str, tmp_size, rhs);

	const auto ret = std::make_unique<String>(tmp_str);
	delete[] tmp_str;
	return *ret;
}

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.string_;
	return os;
}

inline size_t String::max_size()
{
	return SIZE_MAX;
}

inline void String::resize(const size_t length)
{
	if (length == length_)
	{
		return;
	}

	const auto tmp_size = length + 1;
	const auto tmp_length = length;

	auto* tmp_str = create_null_str(tmp_size);

	if (tmp_length >= length_)
	{
		for (size_t i = 0; i < length_; ++i)
		{
			tmp_str[i] = string_[i];
		}

		for (auto i = length_; i < tmp_length; ++i)
		{
			const auto c = ' ';
			tmp_str[i] = c;
		}
	}
	else
	{
		for (size_t i = 0; i < tmp_size; ++i)
		{
			tmp_str[i] = string_[i];
		}
	}

	set_str_props(tmp_size);
	strmove(tmp_str);
}

inline void String::resize(const size_t length, const char c)
{
	if (length == length_)
	{
		return;
	}

	const auto tmp_size = length + 1;
	const auto tmp_length = length;

	auto* tmp_str = create_null_str(tmp_size);

	if (tmp_length < length_)
	{
		for (size_t i = 0; i < tmp_size; ++i)
		{
			tmp_str[i] = string_[i];
		}
	}
	else
	{
		for (size_t i = 0; i < length_; ++i)
		{
			tmp_str[i] = string_[i];
		}

		for (auto i = length_; i < tmp_length; ++i)
		{
			tmp_str[i] = c;
		}
	}

	set_str_props(tmp_size);
	strmove(tmp_str);
}

inline void String::reserve(const size_t capacity)
{
	realloc(capacity);
	capacity_ = capacity;
}

inline void String::push_back(const char c)
{
	append(1, c);
}

inline size_t String::find(const String& str, size_t pos) const noexcept
{
	auto* const result = strstr(string_, str.string_);

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char* s, size_t pos) const
{
	auto* const result = strstr(string_, s);

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char* s, const size_t pos, const size_t n) const
{
	auto* tmp_str = create_null_str(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		tmp_str[i] = s[i];
	}

	auto* const result = strstr(string_, tmp_str);

	delete[] tmp_str;

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char c, const size_t pos) const noexcept
{
	for (auto i = pos; i < length_; ++i)
	{
		if (string_[i] == c)
		{
			return i;
		}
	}

	return npos;
}

inline String& String::replace(const size_t pos, const size_t len, const char* substr)
{
	realloc(size_ + strlen(substr));
	memcpy(string_ + pos, substr, strlen(substr));
	return *this;
}

inline String& String::replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen)
{
	realloc(size_ + str.length_);
	memcpy(string_ + pos, str.string_, str.length_);
	return *this;
}

inline void String::strmove(char* string)
{
	delete[] string_;
	string_ = string;
}

inline char* String::create_null_str(const size_t size)
{
	auto* tmp_str = new char[size];
	memset(tmp_str, '\0', size * sizeof(char));
	return tmp_str;
}

inline void String::alloc(const size_t size)
{
	auto* tmp_str = create_null_str(size);

	if (string_ != nullptr)
	{
		strcpy_s(tmp_str, size, string_);
	}

	strmove(tmp_str);
}

inline void String::realloc(const size_t size)
{
	if (capacity_ < size)
	{
		auto* tmp_str = create_null_str(size);

		if (string_ != nullptr)
		{
			strcpy_s(tmp_str, size, string_);
		}

		strmove(tmp_str);
	}
}

inline void String::set_str_props(const size_t size)
{
	size_ = size;
	length_ = size - 1;
	if (capacity_ < size_)
	{
		capacity_ = size_;
	}
}
