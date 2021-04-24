#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <iostream>

namespace mango
{
	class String
	{
	public:
		String() { reserve(22); }

		String(const char* other)
		{
			set_str_props(strlen(other) + 1);
			alloc(size_);
			strcpy_s(string_, size_, other);
		}

		String(const String& other)
		{
			set_str_props(other.size_);
			alloc(size_);
			strcpy_s(string_, size_, other.string_);
		}

		String(String&& other) noexcept
		{
			set_str_props(other.size_);
			strmove(other.string_);
		}

		~String() { delete[] string_; }

		char& at(const size_t pos)
		{
			if (length_ < pos)
				__debugbreak();
			return string_[pos];
		}

		String& append(const String& str)
		{
			const auto tmp_size = str.size_ + size_;
			realloc(tmp_size);

			strcat_s(string_, tmp_size, str.string_);
			set_str_props(tmp_size);

			return *this;
		}
		String& append(const char* str)
		{
			const auto tmp_size = 1 + strlen(str) + size_;
			realloc(tmp_size);

			strcat_s(string_, tmp_size, str);
			set_str_props(tmp_size);

			return *this;
		}

		String& append(const String& str, const size_t subpos,
			const size_t sublen = npos)
		{
			const auto tmp_size = str.size_ + sublen;
			realloc(tmp_size);

			auto* tmp_str = create_null_str(sublen + 1);

			for (auto i = subpos; i < subpos + sublen; ++i)
				tmp_str[i - subpos] = str[i];

			strcat_s(string_, tmp_size, tmp_str);
			set_str_props(tmp_size);

			delete[] tmp_str;
			return *this;
		}
		String& append(const char* str, const size_t n)
		{
			const auto tmp_size = size_ + n;
			realloc(tmp_size);

			auto* tmp_str = create_null_str(n + 1);

			for (size_t i = 0; i < n; ++i)
				tmp_str[i] = str[i];

			strcat_s(string_, tmp_size, tmp_str);
			set_str_props(tmp_size);

			delete[] tmp_str;
			return *this;
		}
		String& append(const size_t n, const char c)
		{
			auto* tmp_str = create_null_str(n + 1);

			for (size_t i = 0; i < n; ++i)
				tmp_str[i] = c;

			const auto tmp_size = size_ + n;
			realloc(tmp_size);

			strcat_s(string_, tmp_size, tmp_str);
			set_str_props(tmp_size);

			delete[] tmp_str;
			return *this;
		}

		[[nodiscard]] const char& at(const size_t pos) const
		{
			if (length_ < pos)
				__debugbreak();
			return string_[pos];
		}

		char& back()
		{
			if (!empty())
				return string_[length_ - 1];
			else
				return string_[npos];
		}

		[[nodiscard]] char& back() const
		{
			if (!empty())
				return string_[length_ - 1];
			return string_[npos];
		}

		[[nodiscard]] char& front() const
		{
			if (!empty())
				return string_[0];
			return string_[npos];
		}
		char& front()
		{
			if (!empty())
				return string_[0];
			return string_[npos];
		}

		[[nodiscard]] bool empty() const { return length_ == 0; }

		void clear()
		{
			memset(string_, 0, size_);
			length_ = 0;
		}
		[[nodiscard]] const char* c_str() const noexcept { return string_; }

		[[nodiscard]] size_t capacity() const { return capacity_; }
		size_t capacity() { return capacity_; }

		[[nodiscard]] size_t size() const { return size_; }
		size_t size() { return size_; }

		void shrink_to_fit()
		{
			if (capacity_ == size_)
				return;
			alloc(size_);
			capacity_ = size_;
		}

		[[nodiscard]] size_t length() const { return length_; }
		size_t length() { return length_; }

		String& operator=(const String& other)
		{
			if (this == &other)
				return *this;

			set_str_props(other.size_);
			realloc(size_);
			strcpy_s(string_, size_, other.string_);

			return *this;
		}
		String& operator=(const char* str)
		{
			if (string_ == str)
				return *this;

			set_str_props(strlen(str) + 1);
			realloc(size_);
			strcpy_s(string_, capacity_, str);

			return *this;
		}

		constexpr String& operator=(String&& other) noexcept
		{
			if (this == &other)
				return *this;

			set_str_props(other.size_);
			strmove(other.string_);

			return *this;
		}
		char& operator[](const size_t index) const { return string_[index]; }
		char& operator[](const size_t index) { return string_[index]; }
		bool operator==(const String& rhs) const
		{
			return !strcmp(string_, rhs.string_);
		}
		bool operator==(const char* rhs) const { return !strcmp(string_, rhs); }

		String operator+(const String& rhs) const
		{
			const auto tmp_size = rhs.size_ + size_;
			auto* tmp_str = create_null_str(tmp_size);

			strcpy_s(tmp_str, tmp_size, string_);
			strcat_s(tmp_str, tmp_size, rhs.string_);

			const auto ret = std::make_unique<String>(tmp_str);
			delete[] tmp_str;
			return *ret;
		}
		String operator+(const char* rhs) const
		{
			const auto tmp_size = 1 + strlen(rhs) + size_;
			auto* tmp_str = create_null_str(tmp_size);

			strcpy_s(tmp_str, tmp_size, string_);
			strcat_s(tmp_str, tmp_size, rhs);

			const auto ret = std::make_unique<String>(tmp_str);
			delete[] tmp_str;
			return *ret;
		}

		friend std::ostream& operator<<(std::ostream& os, const String& str)
		{
			os << str.string_;
			return os;
		}

		static const size_t npos = -1;
		static size_t max_size() { return SIZE_MAX; }
		void resize(const size_t length)
		{
			if (length == length_)
				return;

			const auto tmp_size = length + 1;
			const auto tmp_length = length;

			auto* tmp_str = create_null_str(tmp_size);

			if (tmp_length < length_)
			{
				for (size_t i = 0; i < tmp_size; ++i)
					tmp_str[i] = string_[i];
			}
			else
			{
				const auto c = ' ';
				for (size_t i = 0; i < length_; ++i)
					tmp_str[i] = string_[i];

				for (auto i = length_; i < tmp_length; ++i)
					tmp_str[i] = c;
			}

			set_str_props(tmp_size);
			strmove(tmp_str);
		}
		void resize(const size_t length, const char c)
		{
			if (length == length_)
				return;

			const auto tmp_size = length + 1;
			const auto tmp_length = length;

			auto* tmp_str = create_null_str(tmp_size);

			if (tmp_length < length_)
			{
				for (size_t i = 0; i < tmp_size; ++i)
					tmp_str[i] = string_[i];
			}
			else
			{
				for (size_t i = 0; i < length_; ++i)
					tmp_str[i] = string_[i];

				for (auto i = length_; i < tmp_length; ++i)
					tmp_str[i] = c;
			}

			set_str_props(tmp_size);
			strmove(tmp_str);
		}

		void reserve(const size_t capacity = 0)
		{
			realloc(capacity);
			capacity_ = capacity;
		}
		void push_back(const char c) { append(1, c); }

		[[nodiscard]] size_t find(const String& str, size_t pos = 0) const noexcept
		{
			auto* const result = strstr(string_, str.string_);

			const size_t index = result - string_;
			if (result == nullptr)
				return npos;

			return index;
		}
		size_t find(const char* s, size_t pos = 0) const
		{
			auto* const result = strstr(string_, s);

			const size_t index = result - string_;
			if (result == nullptr)
				return npos;

			return index;
		}
		size_t find(const char* s, const size_t pos, const size_t n) const
		{
			auto* tmp_str = create_null_str(n + 1);

			for (size_t i = 0; i < n; ++i)
				tmp_str[i] = s[i];

			auto* const result = strstr(string_, tmp_str);

			delete[] tmp_str;

			const size_t index = result - string_;
			if (result == nullptr)
				return npos;

			return index;
		}
		[[nodiscard]] size_t find(const char c, const size_t pos = 0) const noexcept
		{
			for (auto i = pos; i < length_; ++i)
				if (string_[i] == c)
					return i;

			return npos;
		}
		String& replace(const size_t pos, const size_t len, const char* substr)
		{
			realloc(size_ + strlen(substr));
			memcpy(string_ + pos, substr, strlen(substr));
			return *this;
		}
		String& replace(size_t pos, size_t len, const String& str, size_t subpos,
			size_t sublen = npos)
		{
			realloc(size_ + str.length_);
			memcpy(string_ + pos, str.string_, str.length_);
			return *this;
		}

	private:
		char* string_ = nullptr;
		size_t size_{ 0 };
		size_t length_{ 0 };
		size_t capacity_{ 0 };

		void strmove(char* string)
		{
			delete[] string_;
			string_ = string;
		}
		static char* create_null_str(const size_t size)
		{
			auto* tmp_str = new char[size];
			memset(tmp_str, '\0', size * sizeof(char));
			return tmp_str;
		}
		void alloc(const size_t size)
		{
			auto* tmp_str = create_null_str(size);

			if (string_ != nullptr)
				strcpy_s(tmp_str, size, string_);

			strmove(tmp_str);
		}
		void realloc(const size_t size)
		{
			if (capacity_ < size)
			{

				auto* tmp_str = create_null_str(size);

				if (string_ != nullptr)
					strcpy_s(tmp_str, size, string_);

				strmove(tmp_str);
			}
		}
		void set_str_props(const size_t size)
		{
			size_ = size;
			length_ = size - 1;
			if (capacity_ < size_)
			{
				capacity_ = size_;
			}
		}
	};
} // namespace mango
#endif // STRING_HPP
