#pragma once

#include <iostream>

class String
{
public:
	String() = default;
	String(const char* other);
	String(const String& other);
	String(String&& other) noexcept;
	~String();
	char& at(size_t pos);
	String& append(const String& str);
	String& append(const char* str);
	String& append(const String& str, size_t subpos, size_t sublen = npos);
	String& append(const char* str, size_t n);
	String& append(size_t n, char c);
	const char& at(size_t pos) const;
	char& back();
	char& back() const;
	char& front() const;
	char& front();
	bool empty() const;
	void clear();
	const char* c_str() const;
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
	char& operator[](size_t index) const;
	char& operator[](size_t index);
	bool operator==(const String& rhs) const;
	bool operator==(const char* rhs) const;
	String operator+(const String& rhs) const;
	String operator+(const char* rhs) const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	static const size_t npos = -1;
	static size_t max_size();
	void resize(size_t length);
	void resize(size_t length, char c);
	void reserve(size_t capacity = 0);
	void push_back(char c);
	size_t find(const String& str, size_t pos = 0) const;
	size_t find(const char* s, size_t pos = 0) const;
	size_t find(const char* s, size_t pos, size_t n) const;
	size_t find(char c, size_t pos = 0) const;
	String& replace(size_t pos, size_t len, const char* substr);
	String& replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen = npos);

private:
	char* string_ = nullptr;
	size_t size_{ 0 };
	size_t length_{ 0 };
	size_t capacity_{ 0 };

	void allocate(size_t size);
	void set_str_props(size_t size);
};

inline String::String(const char* other)
{
	set_str_props(strlen(other) + 1);
	allocate(this->size());
	strcpy_s(this->string_, this->size(), other);
}

inline String::String(const String& other)
{
	set_str_props(other.size());
	allocate(this->size());
	strcpy_s(this->string_, size(), other.string_);
}

inline String::String(String&& other) noexcept
{
	set_str_props(other.size());
	delete[] string_;
	string_ = other.string_;
}

inline String::~String()
{
	delete[] string_;
}

inline char& String::at(const size_t pos)
{
	if (length() < pos)
	{
		__debugbreak();
	}
	return string_[pos];
}

inline String& String::append(const String& str)
{
	const auto temp_size = str.length() + this->length() + 1;

	if (string_ == nullptr)
	{
		const auto temp = new char[temp_size];
		strcpy_s(temp, temp_size, str.string_);
		string_ = temp;
	}
	else
	{
		allocate(temp_size);
		strcat_s(string_, temp_size, str.string_);
	}
	set_str_props(temp_size);

	return *this;
}

inline String& String::append(const char* str)
{
	const auto temp_size = strlen(str) + this->length() + 1;

	if (string_ == nullptr)
	{
		auto temp = new char[temp_size];
		strcpy_s(temp, temp_size, str);
		string_ = temp;
	}
	else
	{
		allocate(temp_size);
		strcat_s(string_, temp_size, str);
	}
	set_str_props(temp_size);

	return *this;
}

inline String& String::append(const String& str, const size_t subpos, const size_t sublen)
{
	const auto temp_size = str.length() + sublen + 1;
	allocate(temp_size);

	const auto temp = new char[sublen + 1];

	for (size_t i = 0; i < sublen; ++i)
	{
		temp[i] = str[subpos + i];
	}

	temp[sublen] = '\0';

	strcat_s(string_, temp_size, temp);
	set_str_props(temp_size);

	delete[] temp;
	return *this;
}

inline String& String::append(const char* str, const size_t n)
{
	const auto tmp_size = length() + n + 1;
	allocate(tmp_size);

	const auto temp = new char[n + 1];

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = str[i];
	}
	temp[n] = '\0';
	strcat_s(string_, tmp_size, temp);
	set_str_props(tmp_size);

	delete[] temp;
	return *this;
}

inline String& String::append(const size_t n, const char c)
{
	auto* temp = new char[n + 1];

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = c;
	}
	temp[n] = '\0';
	const auto tmp_size = length() + n + 1;
	allocate(tmp_size);

	strcat_s(string_, tmp_size, temp);
	set_str_props(tmp_size);

	delete[] temp;
	return *this;
}

inline const char& String::at(const size_t pos) const
{
	if (length() < pos)
	{
		__debugbreak();
	}
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

	const auto temp = new char[size()];
	strcpy_s(temp, size(), string_);

	delete[] string_;
	string_ = temp;
	set_str_props(size());
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

	set_str_props(other.size());
	allocate(size());
	strcpy_s(string_, size(), other.string_);

	return *this;
}

inline String& String::operator=(const char* str)
{
	if (string_ == str)
	{
		return *this;
	}

	set_str_props(strlen(str) + 1);
	allocate(size());
	strcpy_s(string_, capacity(), str);

	return *this;
}

constexpr auto String::operator=(String&& other) noexcept -> String&
{
	if (this == &other)
	{
		return *this;
	}

	set_str_props(other.size());
	delete[] string_;
	string_ = other.string_;

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
	const auto temp_size = length() + rhs.length() + 1;
	auto temp = new char[temp_size];
	strcpy_s(temp, temp_size, string_);
	strcpy_s(temp, temp_size, rhs.string_);

	const auto ret = std::make_unique<String>(temp);

	delete[] temp;
	return *ret;
}

inline String String::operator+(const char* rhs) const
{
	const auto temp_size = length() + strlen(rhs) + 1;
	auto temp = new char[temp_size];
	strcpy_s(temp, temp_size, string_);
	strcpy_s(temp, temp_size, rhs);

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

	auto* temp = new char[length + 1];

	if (length >= this->length())
	{
		for (size_t i = 0; i < this->length(); ++i)
		{
			temp[i] = string_[i];
		}

		for (auto i = this->length(); i < length; ++i)
		{
			const auto c = ' ';
			temp[i] = c;
		}
	}
	else
	{
		for (size_t i = 0; i < length + 1; ++i)
		{
			temp[i] = string_[i];
		}
	}

	set_str_props(length + 1);
	delete[] string_;
	string_ = temp;
}

inline void String::resize(const size_t length, const char c)
{
	if (length == this->length())
	{
		return;
	}

	auto* tmp_str = new char[length + 1];

	if (length < this->length())
	{
		for (size_t i = 0; i < length + 1; ++i)
		{
			tmp_str[i] = string_[i];
		}
	}
	else
	{
		for (size_t i = 0; i < this->length(); ++i)
		{
			tmp_str[i] = string_[i];
		}

		for (auto i = this->length(); i < length; ++i)
		{
			tmp_str[i] = c;
		}
	}

	tmp_str[length] = '\0';
	set_str_props(length + 1);
	delete[] string_;
	string_ = tmp_str;
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
	auto* temp = new char[n + 1];

	for (size_t i = 0; i < n; ++i)
	{
		temp[i] = s[i];
	}

	auto* const result = strstr(string_, temp);

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
	for (auto i = pos; i < this->length(); ++i)
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

inline String& String::replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen)
{
	allocate(length() + str.length() + 1);
	memcpy(string_ + pos, str.string_, str.length());
	return *this;
}

inline void String::allocate(const size_t size)
{
	if (capacity_ < size)
	{
		auto* temp = new char[size];
		capacity_ = size;
		size_ = size;

		if (string_ != nullptr)
		{
			strcpy_s(temp, size, string_);
		}

		delete[] string_;
		string_ = temp;
	}
}

/**
 * \brief Sets size, length and capacity for normally created string
 * assuming that length = size - 1 and capacity = size.
 * \param size length of string + newline character.
 */
inline void String::set_str_props(const size_t size)
{
	size_ = size;
	length_ = size - 1;
}
