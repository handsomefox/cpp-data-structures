#pragma once

#include "pch.h"
#include "Iterator.h"
#include "StringHelpers.h"

namespace cpp
{
	class String
	{
	public:
		static constexpr size_t npos = -1;
		String() = default;
		String(const char* other)
		{
			const auto capacity = StringHelpers::RequiredCapacity(other);
			SetProps(capacity);
			Alloc(capacity);
			StringHelpers::CopyStr(m_buf, size(), other);
		}
		String(const String& other)
		{
			const auto capacity = StringHelpers::RequiredCapacity(other.c_str());
			SetProps(capacity);
			Alloc(capacity);
			StringHelpers::CopyStr(m_buf, size(), other.c_str());
		}
		String(String&& other) noexcept
		{
			SetProps(other);
			MoveToSelf(other.m_buf);
		}
		~String() { delete[] m_buf; }

		char& at(const size_t pos) { return m_buf[pos]; }
		[[nodiscard]] const char& at(const size_t pos) const { return m_buf[pos]; }

		char& back()
		{
			if (!empty()) return m_buf[length() - 1];
			return m_buf[npos];
		}
		[[nodiscard]] char& back() const
		{
			if (!empty()) return m_buf[length() - 1];
			return m_buf[npos];
		}

		[[nodiscard]] char& front() const
		{
			if (!empty()) return m_buf[0];
			return m_buf[npos];
		}
		char& front()
		{
			if (!empty()) return m_buf[0];
			return m_buf[npos];
		}

		String& append(const String& str)
		{
			const auto capacity = StringHelpers::RequiredCapacity(c_str(), str.c_str());
			if (m_buf == nullptr)
			{
				const auto temp = StringHelpers::AllocTempBuf(capacity);
				StringHelpers::CopyStr(temp, capacity, str.m_buf);
				MoveToSelf(temp);
			}
			else
			{
				Alloc(capacity);
				StringHelpers::CatStr(m_buf, capacity, str.m_buf);
			}
			SetProps(capacity);
			return *this;
		}
		String& append(const char* str)
		{
			const auto capacity = StringHelpers::RequiredCapacity(c_str(), str);
			if (m_buf == nullptr)
			{
				const auto temp = StringHelpers::AllocTempBuf(capacity);
				StringHelpers::CopyStr(temp, capacity, str);
				MoveToSelf(temp);
			}
			else
			{
				Alloc(capacity);
				StringHelpers::CatStr(m_buf, capacity, str);
			}
			SetProps(capacity);
			return *this;
		}
		String& append(const String& str, const size_t subpos, const size_t sublen = npos)
		{
			const auto capacity = str.size() + sublen;
			Alloc(capacity);

			const auto temp = StringHelpers::AllocTempBuf(sublen + 1);

			for (size_t i = 0; i < sublen; ++i)
				temp[i] = str[subpos + i];

			temp[sublen] = '\0';

			StringHelpers::CatStr(m_buf, capacity, temp);
			SetProps(capacity);

			delete[] temp;
			return *this;
		}
		String& append(const char* str, const size_t n)
		{
			const auto capacity = size() + n;
			Alloc(capacity);

			const auto temp = StringHelpers::AllocTempBuf(n + 1);

			for (size_t i = 0; i < n; ++i)
				temp[i] = str[i];

			temp[n] = '\0';

			StringHelpers::CatStr(m_buf, capacity, temp);
			SetProps(capacity);

			delete[] temp;
			return *this;
		}
		String& append(const size_t n, const char c)
		{
			const auto temp = StringHelpers::AllocTempBuf(n + 1);

			for (size_t i = 0; i < n; ++i)
				temp[i] = c;

			temp[n] = '\0';

			const auto capacity = size() + n;
			Alloc(capacity);

			StringHelpers::CatStr(m_buf, capacity, temp);
			SetProps(capacity);

			delete[] temp;
			return *this;
		}

		[[nodiscard]] bool empty() const { return length() == 0; }

		void clear()
		{
			memset(m_buf, 0, size());
			m_length = 0;
		}

		[[nodiscard]] const char* c_str() const { return m_buf; }

		[[nodiscard]] size_t capacity() const { return m_capacity; }
		size_t capacity() { return m_capacity; }

		[[nodiscard]] size_t size() const { return m_size; }
		size_t size() { return m_size; }

		[[nodiscard]] size_t length() const { return m_length; }
		size_t length() { return m_length; }

		void shrink_to_fit()
		{
			if (capacity() == size())
				return;

			const auto shrinked_capacity = size();
			const auto shrinked_string = StringHelpers::AllocTempBuf(shrinked_capacity);
			StringHelpers::CopyStr(shrinked_string, shrinked_capacity, m_buf);

			MoveToSelf(shrinked_string);
			SetProps(size());
			m_capacity = size();
		}
		static size_t max_size() { return SIZE_MAX; }

		void resize(const size_t length)
		{
			if (length == this->length())
				return;

			const auto capacity = length + 1;
			const auto temp = StringHelpers::AllocTempBuf(capacity);

			if (length >= this->length())
			{
				for (size_t i = 0; i < this->length(); ++i)
					temp[i] = m_buf[i];

				for (auto i = this->length(); i < length; ++i)
					temp[i] = ' ';
			}
			else
				for (size_t i = 0; i < capacity; ++i)
					temp[i] = m_buf[i];

			SetProps(capacity);
			MoveToSelf(temp);
		}
		void resize(const size_t length, const char c)
		{
			if (length == this->length())
				return;

			const auto capacity = length + 1;
			const auto temp = StringHelpers::AllocTempBuf(capacity);

			if (length < this->length())
				for (size_t i = 0; i < capacity; ++i)
					temp[i] = m_buf[i];
			else
			{
				for (size_t i = 0; i < this->length(); ++i)
					temp[i] = m_buf[i];

				for (auto i = this->length(); i < length; ++i)
					temp[i] = c;
			}
			temp[length] = '\0';

			SetProps(capacity);
			MoveToSelf(temp);
		}
		void reserve(const size_t capacity = 0) { Alloc(capacity); }

		void push_back(const char c) { append(1, c); }

		String& replace(const size_t pos, size_t len, const char* substr)
		{
			Alloc(size() + strlen(substr));
			memcpy(m_buf + pos, substr, strlen(substr));
			return *this;
		}
		String& replace(const size_t pos, size_t len, const String& str, size_t subpos, size_t sublen = npos)
		{
			Alloc(length() + str.length() + 1);
			memcpy(m_buf + pos, str.m_buf, str.length());
			return *this;
		}

		[[nodiscard]] size_t find(const String& str, size_t pos = 0) const
		{
			const auto result = StringHelpers::SubStr(m_buf, str.m_buf);

			const size_t index = result - m_buf;
			if (result == nullptr)
				return npos;

			return index;
		}
		size_t find(const char* s, size_t pos = 0) const
		{
			const auto result = StringHelpers::SubStr(m_buf, s);

			const size_t index = result - m_buf;
			if (result == nullptr)
				return npos;

			return index;
		}
		size_t find(const char* s, size_t pos, size_t n) const
		{
			const auto temp = StringHelpers::AllocTempBuf(n + 1);

			for (size_t i = 0; i < n; ++i)
				temp[i] = s[i];

			const auto result = StringHelpers::SubStr(m_buf, temp);

			delete[] temp;

			const size_t index = result - m_buf;
			if (result == nullptr)
				return npos;

			return index;
		}
		[[nodiscard]] size_t find(const char c, const size_t pos = 0) const
		{
			for (auto i = pos; i < length(); ++i)
				if (m_buf[i] == c)
					return i;

			return npos;
		}

		String& operator=(const String& other)
		{
			if (this == &other)
				return *this;

			SetProps(other);
			Alloc(size());
			StringHelpers::CopyStr(m_buf, size(), other.m_buf);

			return *this;
		}
		String& operator=(const char* str)
		{
			if (m_buf == str)
				return *this;

			const auto cap = StringHelpers::RequiredCapacity(str);
			SetProps(cap);
			Alloc(cap);
			StringHelpers::CopyStr(m_buf, size(), str);

			return *this;
		}
		constexpr String& operator=(String&& other) noexcept
		{
			if (this == &other)
				return *this;

			SetProps(other);
			MoveToSelf(other.m_buf);

			return *this;
		}
		char& operator[](const size_t index) const { return m_buf[index]; }
		char& operator[](const size_t index) { return m_buf[index]; }

		bool operator==(const String& rhs) const { return !strcmp(m_buf, rhs.m_buf); }
		bool operator==(const char* rhs) const { return !strcmp(m_buf, rhs); }

		String operator+(const String& rhs) const
		{
			const auto capacity = StringHelpers::RequiredCapacity(c_str(), rhs.c_str());
			const auto temp = StringHelpers::AllocTempBuf(capacity);
			StringHelpers::CopyStr(temp, capacity, m_buf);
			StringHelpers::CatStr(temp, capacity, rhs.m_buf);

			const auto ret = std::make_unique<String>(temp);

			delete[] temp;
			return *ret;
		}
		String operator+(const char* rhs) const
		{
			const auto capacity = StringHelpers::RequiredCapacity(c_str(), rhs);
			auto temp = StringHelpers::AllocTempBuf(capacity);
			StringHelpers::CopyStr(temp, capacity, m_buf);
			StringHelpers::CatStr(temp, capacity, rhs);

			const auto ret = std::make_unique<String>(temp);

			delete[] temp;
			return *ret;
		}
		std::ostream& operator<<(std::ostream& os) const
		{
			os << this->m_buf;
			return os;
		}

		using ConstIterator = Iterator<const String, const char>;
		[[nodiscard]] constexpr ConstIterator begin() const { return ConstIterator::begin(*this); }
		[[nodiscard]] constexpr ConstIterator end() const { return ConstIterator::end(*this); }

	private:
		char* m_buf = nullptr;
		size_t m_size{ 0 };
		size_t m_length{ 0 };
		size_t m_capacity{ 0 };

		void Alloc(const size_t size)
		{
			if (m_capacity < size)
			{
				const auto temp = StringHelpers::AllocTempBuf(size);
				m_capacity = size;
				m_size = size;

				if (m_buf != nullptr)
					StringHelpers::CopyStr(temp, size, m_buf);

				MoveToSelf(temp);
			}
		}
		void SetProps(const size_t size)
		{
			m_size = size;
			m_length = size - 1;
		}
		void SetProps(const String& string)
		{
			m_size = string.m_size;
			m_length = string.m_length;
			m_capacity = string.m_capacity;
		}
		void MoveToSelf(char* string)
		{
			delete[] m_buf;
			m_buf = string;
		}
	};
}
