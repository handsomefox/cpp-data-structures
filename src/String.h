#pragma once

#include "pch.h"

#include "Iterator.h"
#include <cstring>

namespace cpp
{
	class String
	{
	public:
		// npos is a static member constant value with the greatest possible value for an element of type size_t.
		// This constant is defined with a value of -1, which because size_t is an unsigned integral type,
		// it is the largest possible representable value for this type.
		static constexpr size_t npos = -1;

		// Constructs an empty string, with a length of zero characters.
		String() = default;

		// Destroys the string object.
		~String() = default;

		// Copies the null-terminated character sequence (C-string) pointed by s.
		String(const char* other)
		{
			auto length = strlen(other) + 1;
			auto buffer = new char[length];

			strcpy_s(buffer, length, other);
			m_data = {buffer, length - 1, length};
		}

		// Constructs a copy of str.
		String(const String& other)
		{
			auto buffer = new char[other.capacity()];
			strcpy_s(buffer, other.capacity(), other.m_data.buf);
			m_data = {buffer, other.size(), other.capacity()};
		}

		// Acquires the contents of str.
		String(String&& other) noexcept
		{
			m_data = other.m_data;
		}

		// Returns a reference to the character at position pos in the string.
		// The function automatically checks whether pos is the valid position of a
		// character in the string (i.e., whether pos is less than the string length),
		// throwing an out_of_range exception if it is not.
		char& at(const size_t pos)
		{
			if (pos > length())
			{
				throw std::out_of_range("Position outside of string");
			}
			return m_data.buf[pos];
		}

		// Returns a reference to the character at position pos in the string.
		// The function automatically checks whether pos is the valid position of a
		// character in the string (i.e., whether pos is less than the string length),
		// throwing an out_of_range exception if it is not.
		[[nodiscard]] const char& at(const size_t pos) const
		{
			if (pos > length())
			{
				throw std::out_of_range("Position outside of string");
			}
			return m_data.buf[pos];
		}

		// Returns a reference to the last character of the string.
		// This function shall not be called on empty strings.
		[[nodiscard]] char& back()
		{
			return m_data.buf[size() - 1];
		}

		// Returns a reference to the last character of the string.
		// This function shall not be called on empty strings.
		[[nodiscard]] char& back() const
		{
			return m_data.buf[size() - 1];
		}

		// Returns a reference to the first character of the string.
		// This function shall not be called on empty strings.
		[[nodiscard]] char& front() const
		{
			return m_data.buf[0];
		}

		// Returns a reference to the first character of the string.
		// This function shall not be called on empty strings.
		[[nodiscard]] char& front()
		{
			return m_data.buf[0];
		}

		// Appends a copy of str.
		String& append(const String& str)
		{
			return this->append(str.c_str());
		}

		// Appends a copy of the string formed by the null-terminated
		// character sequence (C-string) pointed by s.
		String& append(const char* str)
		{
			auto sz = length() + strlen(str) + 1;
			auto buffer = new char[sz];

			strcpy_s(buffer, sz, c_str());
			strcat_s(buffer, sz, str);

			m_data.move(buffer);
			m_data.size = sz - 1;
			m_data.capacity = sz;

			return *this;
		}

		// Appends a copy of a substring of str. The substring is the portion of str that
		// begins at the character position subpos and spans sublen characters
		// (or until the end of str, if either str is too short or if sublen is string::npos).
		String& append(const String& str, const size_t subpos, const size_t sublen = npos)
		{
			auto sub = str.substr(subpos, sublen);
			return this->append(sub.c_str());
		}

		// Appends a copy of the first n characters in the array of characters pointed by s.
		String& append(const char* s, const size_t n)
		{
			auto buffer = new char[n + 1];
			strncpy_s(buffer, sizeof(buffer), s, n);
			this->append(buffer);
			delete[] buffer;

			return *this;
		}

		// Appends n consecutive copies of character c.
		String& append(const size_t n, const char c)
		{
			auto sz = length() + n + 1;
			auto buffer = new char[sz];

			auto copy_buffer = new char[n + 1];
			for (size_t i = 0; i < n; ++i)
			{
				copy_buffer[i] = c;
			}
			copy_buffer[n] = '\0';

			strcpy_s(buffer, sz, c_str());
			strcat_s(buffer, sz, copy_buffer);

			m_data.move(buffer);
			m_data.capacity = sz;
			m_data.size = sz - 1;

			delete[] copy_buffer;
			return *this;
		}

		// Returns whether the string is empty (i.e. whether its length is 0).
		[[nodiscard]] bool empty() const
		{
			return length() == 0;
		}

		// Erases the contents of the string, which becomes an empty string (with a length of 0 characters).
		void clear()
		{
			m_data.size = 0;
		}

		// Returns a pointer to an array that contains a null-terminated sequence of characters
		// (i.e., a C-string) representing the current value of the string object.
		//
		// This array includes the same sequence of characters that make up the value of the string
		// object plus an additional terminating null-character ('\0') at the end.
		[[nodiscard]] const char* c_str() const
		{
			return m_data.buf;
		}

		// Returns the size of the storage space currently allocated for the string, expressed in terms of bytes.
		[[nodiscard]] size_t capacity() const
		{
			return m_data.capacity;
		}

		// Returns the size of the storage space currently allocated for the string, expressed in terms of bytes.
		[[nodiscard]] size_t capacity()
		{
			return m_data.capacity;
		}

		// Returns the length of the string, in terms of bytes.
		[[nodiscard]] size_t size() const
		{
			return m_data.size;
		}

		// Returns the length of the string, in terms of bytes.
		[[nodiscard]] size_t size()
		{
			return m_data.size;
		}

		// Returns the length of the string, in terms of bytes.
		[[nodiscard]] size_t length() const
		{
			return m_data.size;
		}

		// Returns the length of the string, in terms of bytes.
		[[nodiscard]] size_t length()
		{
			return m_data.size;
		}

		// Requests the string to reduce its capacity to fit its size.
		void shrink_to_fit()
		{
			if (size() == capacity())
				return;

			auto buffer = new char[size()];
			strcpy_s(buffer, sizeof(buffer), this->m_data.buf);

			m_data.move(buffer);
			m_data.capacity = size();
		}

		// Returns the maximum length the string can reach.
		static size_t max_size()
		{
			return npos;
		}

		// Resizes the string to a length of n characters.
		//
		// If n is smaller than the current string length,
		// the current value is shortened to its first n character,
		// removing the characters beyond the nth.
		//
		// If n is greater than the current string length, the current
		// content is extended by inserting at the end as many characters
		// as needed to reach a size of n. If c is specified, the new
		// elements are initialized as copies of c, otherwise,
		// they are value-initialized characters (null characters).
		void resize(const size_t n, const char c = '\0')
		{
			size_t sz;
			char* buffer;
			if (n < length())
			{
				sz = n + 1;
				buffer = new char[sz];
				strncpy_s(buffer, sz, c_str(), n);
			}
			else
			{
				sz = length() + n + 1;
				buffer = new char[sz];
				strcpy_s(buffer, sz, this->m_data.buf);
				strncpy_s(buffer + length(), sz, &c, n);
			}
			m_data.move(buffer);
			m_data.size = sz;
		}

		// Requests that the string capacity be adapted to a planned change in
		// size to a length of up to n characters.
		//
		// If n is greater than the current string capacity, the function causes
		// the container to increase its capacity to n characters (or greater).
		//
		// In all other cases, it is taken as a non-binding request to shrink the
		// string capacity: the container implementation is free to optimize
		// otherwise and leave the string with a capacity greater than n.
		//
		// This function has no effect on the string length and cannot alter its content.
		void reserve(const size_t n = 0)
		{
			if (capacity() == n)
				return;

			if (length() > n)
			{
				shrink_to_fit();
				return;
			}

			auto buffer = new char[n];
			strcpy_s(buffer, n, m_data.buf);
			m_data.move(buffer);
			m_data.capacity = n;
		}

		// Appends character c to the end of the string, increasing its length by one.
		void push_back(const char c)
		{
			this->append(&c);
		}

		// Copies str.
		String& replace(const size_t pos, size_t len, const char* substr)
		{
			auto sz = size() + strlen(substr);
			auto buffer = new char[sz + 1];

			strcpy_s(buffer, sz, c_str());
			strcat_s(buffer, sz, substr);

			m_data.move(buffer);
			m_data.size = sz;
			m_data.capacity = sz;

			return *this;
		}

		[[nodiscard]] size_t find(const String& str, size_t pos = 0) const
		{
			const auto result = strstr(c_str(), str.c_str());

			const size_t index = result - c_str();
			if (result == nullptr)
				return npos;

			return index;
		}

		// Searches the string for the first occurrence of the sequence specified by its arguments.
		[[nodiscard]] size_t find(const char* s, size_t pos = 0) const
		{
			const auto result = strstr(c_str(), s);

			const size_t index = result - c_str();
			if (result == nullptr)
				return npos;

			return index;
		}

		// Searches the string for the first occurrence of the sequence specified by its arguments.
		// n - Length of sequence of characters to match.
		[[nodiscard]] size_t find(const char* s, size_t pos, size_t n) const
		{
			const auto temp = new char[n + 1];

			for (size_t i = 0; i < n; ++i)
				temp[i] = s[i];

			const auto result = strstr(c_str(), temp);

			const size_t index = result - c_str();
			delete[] temp;

			if (result == nullptr)
				return npos;

			return index;
		}

		// Searches the string for the first occurrence of the sequence specified by its arguments.
		// Individual character to be searched for.
		[[nodiscard]] size_t find(const char c, const size_t pos = 0) const
		{
			for (auto i = pos; i < length(); ++i)
				if (m_data.buf[i] == c)
					return i;

			return npos;
		}

		// Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
		[[nodiscard]] String substr(size_t pos = 0, size_t len = npos) const
		{
			if (pos > length() || pos + len > length())
			{
				return {};
			}

			size_t sz = 0;

			if (len == npos)
			{
				sz = length() - pos;
			}
			else
			{
				sz = len + 1;
			}

			auto buffer = new char[sz];
			memcpy(buffer, &c_str()[pos], len);
			buffer[sz - 1] = '\0';

			return {buffer};
		}

		// Assigns a new value to the string, replacing its current contents.
		String& operator=(const String& other)
		{
			if (this == &other)
				return *this;

			if (capacity() < other.length())
			{
				*this = String(other.c_str());
				return *this;
			}

			memset(m_data.buf, '\0', length());
			strcpy_s(m_data.buf, capacity(), other.c_str());
			m_data.size = other.size();

			return *this;
		}

		// Assigns a new value to the string, replacing its current contents.
		String& operator=(const char* str)
		{
			if (m_data.buf == str)
				return *this;

			auto len = strlen(str);

			if (capacity() < len + 1)
			{
				*this = String(str);
				return *this;
			}

			memset(m_data.buf, '\0', length());
			strcpy_s(m_data.buf, capacity(), str);
			m_data.size = len + 1;

			return *this;
		}

		// Assigns a new value to the string, replacing its current contents.
		constexpr String& operator=(String&& other) noexcept
		{
			if (this == &other)
				return *this;

			this->m_data = other.m_data;
			return *this;
		}

		// Returns a reference to the character at position `index` in the string.
		char& operator[](const size_t index) const
		{
			return m_data.buf[index];
		}

		// Returns a reference to the character at position `index` in the string.
		char& operator[](const size_t index)
		{
			return m_data.buf[index];
		}

		// This function performs a binary comparison of the characters inside the strings.
		bool operator==(const String& rhs) const
		{
			return !strcmp(c_str(), rhs.c_str());
		}

		// 		// This function performs a binary comparison of the characters inside the strings.
		bool operator==(const char* rhs) const
		{
			return !strcmp(c_str(), rhs);
		}

		// Returns a newly constructed string object with its value being the concatenation
		// of the characters in lhs followed by those of rhs.
		String operator+(const String& rhs) const
		{
			auto capacity = this->length() + rhs.length() + 1;
			auto buffer = new char[capacity];

			strcpy_s(buffer, capacity, c_str());
			strcat_s(buffer, capacity, rhs.c_str());

			return {buffer};
		}

		// Returns a newly constructed string object with its value being the concatenation
		// of the characters in lhs followed by those of rhs.
		String operator+(const char* rhs) const
		{
			auto capacity = this->length() + strlen(rhs) + 1;
			auto buffer = new char[capacity];

			strcpy_s(buffer, capacity, c_str());
			strcat_s(buffer, capacity, rhs);

			return {buffer};
		}

		// Inserts the sequence of characters that conforms value of String into os.
		std::ostream& operator<<(std::ostream& os) const
		{
			return os << m_data.buf;
		}

		using It = Iterator<String, const char>;
		constexpr It begin()
		{
			return It::begin(*this);
		}

		constexpr It end()
		{
			return It::end(*this);
		}

		using ConstIt = Iterator<const String, const char>;
		[[nodiscard]] constexpr ConstIt begin() const
		{
			return ConstIt::begin(*this);
		}

		[[nodiscard]] constexpr ConstIt end() const
		{
			return ConstIt::end(*this);
		}

	private:
		struct StringData {
			char* buf;
			size_t size, capacity;

			void drop() const
			{
				delete[] buf;
			}

			void move(char* buffer)
			{
				drop();
				buf = buffer;
			}

			~StringData()
			{
				this->drop();
			}
		};

		StringData m_data{};
	};
}// namespace cpp
