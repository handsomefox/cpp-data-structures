#pragma once

#include <ostream>
#include "Iterator.hpp"
#ifdef container_type
#undef container_type
#define container_type String
#endif

class String
{
public:
	String() = default;
	String(const char* other);
	String(const String& other);
	String(String&& other) noexcept;

	~String();

	char& at(size_t pos);
	[[nodiscard]] const char& at(size_t pos) const;

	char& back();
	[[nodiscard]] char& back() const;
	[[nodiscard]] char& front() const;
	char& front();

	static constexpr size_t npos = -1;

	String& append(const String& str);
	String& append(const char* str);
	String& append(const String& str, size_t subpos, size_t sublen = npos);
	String& append(const char* str, size_t n);
	String& append(size_t n, char c);


	[[nodiscard]] bool empty() const;
	void clear();

	[[nodiscard]] const char* c_str() const;

	[[nodiscard]] size_t capacity() const;
	size_t capacity();
	[[nodiscard]] size_t size() const;
	size_t size();
	[[nodiscard]] size_t length() const;
	size_t length();

	void shrink_to_fit();
	static size_t max_size();
	void resize(size_t length);
	void resize(size_t length, char c);
	void reserve(size_t capacity = 0);


	void push_back(char c);
	String& replace(size_t pos, size_t len, const char* substr);
	String& replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen = npos);

	[[nodiscard]] size_t find(const String& str, size_t pos = 0) const;
	size_t find(const char* s, size_t pos = 0) const;
	size_t find(const char* s, size_t pos, size_t n) const;
	[[nodiscard]] size_t find(char c, size_t pos = 0) const;

	String& operator=(const String& other);
	String& operator=(const char* str);
	constexpr String& operator=(String&& other) noexcept;
	char& operator[](size_t index) const;
	char& operator[](size_t index);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs) const;
	String operator+(const String& rhs) const;
	String operator+(const char* rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);

	[[nodiscard]] Iterator begin() const;
	[[nodiscard]] Iterator end() const;
private:

	char* string_ = nullptr;
	size_t size_{ 0 };
	size_t length_{ 0 };
	size_t capacity_{ 0 };

	void allocate(size_t size);
	void set_string_properties(size_t size);
	void set_string_properties(const String& string);
	static size_t calculate_required_capacity(const char* lhs, const char* rhs);
	static size_t calculate_required_capacity(const char* string);
	[[nodiscard]] static char* allocate_temp_buffer(size_t size);
	void copy_string(char* dst, size_t buff_size, char const* src) const;
	void concat_string(char* dst, size_t buff_size, char const* src) const;
	void take_ownership_of_string(char* string);
	const char* find_substring(const char* string, const char* find) const;
	char* find_substring(char* string, const char* find) const;
};

inline String::String(const char* other)
{
	const auto capacity = calculate_required_capacity(other);
	set_string_properties(capacity);
	allocate(capacity);
	copy_string(string_, size(), other);
}

inline String::String(const String& other)
{
	const auto capacity = calculate_required_capacity(other.c_str());
	set_string_properties(capacity);
	allocate(capacity);
	copy_string(string_, size(), other.c_str());
}

inline String::String(String&& other) noexcept
{
	set_string_properties(other);
	take_ownership_of_string(other.string_);
}

inline String::~String()
{
	delete[] string_;
}

inline char& String::at(const size_t pos)
{
	//if (length() < pos)
	//{
	//	__debugbreak();
	//}
	return string_[pos];
}

inline String& String::append(const String& str)
{
	const auto capacity = calculate_required_capacity(c_str(), str.c_str());

	if (string_ == nullptr)
	{
		const auto temp = allocate_temp_buffer(capacity);
		copy_string(temp, capacity, str.string_);
		take_ownership_of_string(temp);
	}
	else
	{
		allocate(capacity);
		concat_string(string_, capacity, str.string_);
	}
	set_string_properties(capacity);

	return *this;
}

inline String& String::append(const char* str)
{
	const auto capacity = calculate_required_capacity(c_str(), str);

	if (string_ == nullptr)
	{
		const auto temp = allocate_temp_buffer(capacity);
		copy_string(temp, capacity, str);
		take_ownership_of_string(temp);
	}
	else
	{
		allocate(capacity);
		concat_string(string_, capacity, str);
	}
	set_string_properties(capacity);

	return *this;
}

inline String& String::append(const String& str, const size_t subpos, const size_t sublen)
{
	const auto capacity = str.size() + sublen;
	allocate(capacity);

	const auto temp = allocate_temp_buffer(sublen + 1);

	for (size_t i = 0; i < sublen; ++i)
	{
		temp[i] = str[subpos + i];
	}
	temp[sublen] = '\0';

	concat_string(string_, capacity, temp);
	set_string_properties(capacity);

	delete[] temp;
	return *this;
}

inline String& String::append(const char* str, const size_t n)
{
	const auto capacity = size() + n;
	allocate(capacity);

	const auto temp = allocate_temp_buffer(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = str[i];
	}
	temp[n] = '\0';

	concat_string(string_, capacity, temp);
	set_string_properties(capacity);

	delete[] temp;
	return *this;
}

inline String& String::append(const size_t n, const char c)
{
	const auto temp = allocate_temp_buffer(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = c;
	}
	temp[n] = '\0';

	const auto capacity = size() + n;
	allocate(capacity);

	concat_string(string_, capacity, temp);
	set_string_properties(capacity);

	delete[] temp;
	return *this;
}

inline const char& String::at(const size_t pos) const
{
	//if (length() < pos)
	//{
	//	__debugbreak();
	//}
	return string_[pos];
}

inline char& String::back()
{
	if (!empty())
	{
		return string_[length() - 1];
	}
	return string_[npos];
}

inline char& String::back() const
{
	if (!empty())
	{
		return string_[length() - 1];
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
	return length() == 0;
}

inline void String::clear()
{
	memset(string_, 0, size());
	length_ = 0;
}

inline const char* String::c_str() const
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
	if (capacity() == size())
	{
		return;
	}
	const auto required_capacity = size();
	const auto string = allocate_temp_buffer(required_capacity);
	copy_string(string, required_capacity, string_);

	take_ownership_of_string(string);
	set_string_properties(size());
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

	set_string_properties(other);
	allocate(size());
	copy_string(string_, size(), other.string_);

	return *this;
}

inline String& String::operator=(const char* str)
{
	if (string_ == str)
	{
		return *this;
	}

	set_string_properties(str);
	allocate(size());
	copy_string(string_, size(), str);

	return *this;
}

constexpr String& String::operator=(String&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	set_string_properties(other);
	take_ownership_of_string(other.string_);

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
	const auto capacity = calculate_required_capacity(c_str(), rhs.c_str());
	const auto temp = allocate_temp_buffer(capacity);
	copy_string(temp, capacity, string_);
	concat_string(temp, capacity, rhs.string_);

	const auto ret = std::make_unique<String>(temp);

	delete[] temp;
	return *ret;
}

inline String String::operator+(const char* rhs) const
{
	const auto capacity = calculate_required_capacity(c_str(), rhs);
	auto temp = allocate_temp_buffer(capacity);
	copy_string(temp, capacity, string_);
	concat_string(temp, capacity, rhs);

	const auto ret = std::make_unique<String>(temp);

	delete[] temp;
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
	if (length == this->length())
	{
		return;
	}

	const auto capacity = length + 1;
	const auto temp = allocate_temp_buffer(capacity);

	if (length >= this->length())
	{
		for (size_t i = 0; i < this->length(); ++i)
		{
			temp[i] = string_[i];
		}

		for (auto i = this->length(); i < length; ++i)
		{
			constexpr auto c = ' ';
			temp[i] = c;
		}
	}
	else
	{
		for (size_t i = 0; i < capacity; ++i)
		{
			temp[i] = string_[i];
		}
	}

	set_string_properties(capacity);
	take_ownership_of_string(temp);
}

inline void String::resize(const size_t length, const char c)
{
	if (length == this->length())
	{
		return;
	}

	const auto capacity = length + 1;
	const auto temp = allocate_temp_buffer(capacity);

	if (length < this->length())
	{
		for (size_t i = 0; i < capacity; ++i)
		{
			temp[i] = string_[i];
		}
	}
	else
	{
		for (size_t i = 0; i < this->length(); ++i)
		{
			temp[i] = string_[i];
		}

		for (auto i = this->length(); i < length; ++i)
		{
			temp[i] = c;
		}
	}
	temp[length] = '\0';

	set_string_properties(capacity);
	take_ownership_of_string(temp);
}

inline void String::reserve(const size_t capacity)
{
	allocate(capacity);
}

inline void String::push_back(const char c)
{
	append(1, c);
}

inline size_t String::find(const String& str, size_t pos) const
{
	const auto result = find_substring(string_, str.string_);

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char* s, size_t pos) const
{
	const auto result = find_substring(string_, s);

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char* s, const size_t pos, const size_t n) const
{
	const auto temp = allocate_temp_buffer(n + 1);

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = s[i];
	}

	const auto result = find_substring(string_, temp);

	delete[] temp;

	const size_t index = result - string_;
	if (result == nullptr)
	{
		return npos;
	}

	return index;
}

inline size_t String::find(const char c, const size_t pos) const
{
	for (auto i = pos; i < length(); ++i)
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
	allocate(size() + strlen(substr));
	memcpy(string_ + pos, substr, strlen(substr));
	return *this;
}

// TODO: Implement using subpos and sublen
inline String& String::replace(const size_t pos, size_t len, const String& str, size_t subpos, size_t sublen)
{
	allocate(length() + str.length() + 1);
	memcpy(string_ + pos, str.string_, str.length());
	return *this;
}

inline Iterator String::begin() const
{
	return Iterator(&string_[0]);
}
inline Iterator String::end() const
{
	return Iterator(&string_[size_]);
}

inline void String::allocate(const size_t size)
{
	if (capacity_ < size)
	{
		const auto temp = allocate_temp_buffer(size);
		capacity_ = size;
		size_ = size;

		if (string_ != nullptr)
		{
			copy_string(temp, size, string_);
		}

		take_ownership_of_string(temp);
	}
}

inline void String::set_string_properties(const size_t size)
{
	size_ = size;
	length_ = size - 1;
}

inline void String::set_string_properties(const String& string)
{
	size_ = string.size_;
	length_ = string.length_;
	capacity_ = string.capacity_;
}

inline size_t String::calculate_required_capacity(const char* lhs, const char* rhs)
{
	size_t l{ 0 }, r{ 0 };
	if (lhs != nullptr)
	{
		l = strlen(lhs);
	}
	if (rhs != nullptr)
	{
		r = strlen(rhs);
	}
	return l + r + 1;
}

inline size_t String::calculate_required_capacity(const char* string)
{
	if (string != nullptr)
		return strlen(string) + 1;
	return 0;
}

inline char* String::allocate_temp_buffer(const size_t size)
{
	const auto temp = new char[size];
	return temp;
}

inline void String::copy_string(char* dst, const size_t buff_size, char const* src) const
{
	strcpy_s(dst, buff_size, src);
}

inline void String::concat_string(char* dst, const size_t buff_size, char const* src) const
{
	strcat_s(dst, buff_size, src);
}

inline void String::take_ownership_of_string(char* string)
{
	delete[] string_;
	string_ = string;
}

inline const char* String::find_substring(const char* string, const char* find) const
{
	return strstr(string, find);
}

inline char* String::find_substring(char* string, const char* find) const
{
	return strstr(string, find);
}
