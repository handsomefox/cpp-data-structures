#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <iostream>

namespace mango
{
	template <typename Array>
	struct ArrIter
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = Array;
		using difference_type = std::ptrdiff_t;
		using pointer = Array*;
		using reference = Array&;

		ArrIter(pointer ptr) : m_ptr(ptr)
		{
		}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		ArrIter& operator++()
		{
			++m_ptr;
			return *this;
		}

		ArrIter operator++(Array)
		{
			ArrIter tmp = *this;
			++*this;
			return tmp;
		}

		friend bool operator==(const ArrIter& a, const ArrIter& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const ArrIter& a, const ArrIter& b) { return a.m_ptr != b.m_ptr; }

	private:
		pointer m_ptr = nullptr;
	};

	template <typename T, size_t N>
	class Array
	{
	public:
		Array() = default;

		constexpr bool empty() { return N == 0; }
		constexpr size_t size() noexcept { return N; }
		constexpr T* data() noexcept { return data_; }
		[[nodiscard]] constexpr const T* data() const noexcept { return data_; }

		constexpr const T& operator[](const size_t& index) const noexcept
		{
			return data_[index];
		}

		constexpr T& operator[](const size_t& index) noexcept { return data_[index]; }

		ArrIter<T> begin()
		{
			return ArrIter<T>(&data_[0]);
		}

		ArrIter<T> end()
		{
			return ArrIter<T>(&data_[N]);
		}

	private:
		T data_[N];
	};
} // namespace mango
#endif // ARRAY_HPP
