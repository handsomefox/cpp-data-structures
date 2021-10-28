#pragma once
#include "Iterator.h"

namespace cpp {
	template <typename T, size_t N>
	class Array {
	public:
		constexpr Array() = default;
		constexpr Array(const std::initializer_list<T>& list)
		{
			size_t count = 0;
			for (auto const& element : list)
			{
				m_data[count] = element;
				++count;
			}
		}
		constexpr size_t size() noexcept { return N; }

		constexpr T& operator[](const size_t& index) noexcept { return m_data[index]; }
		constexpr const T& operator[](const size_t& index) const noexcept { return m_data[index]; }

		[[nodiscard]] constexpr const T& at(size_t index) const { return m_data[index]; }
		constexpr T& at(size_t index) { return m_data[index]; }

		[[nodiscard]] constexpr const T& front() const { return m_data[0]; }
		constexpr T& front() { return m_data[0]; }

		[[nodiscard]] constexpr const T& back() const { return m_data[N - 1]; }
		constexpr T& back() { return m_data[N]; }

		constexpr T* data() noexcept { return m_data; }
		[[nodiscard]] constexpr const T* data() const noexcept { return m_data; }

		constexpr bool empty() noexcept { return N == 0; }

		[[nodiscard]] constexpr size_t max_size() const noexcept { return std::distance(begin(), end()); }

		void fill(const T& value) { std::fill(begin(), end(), value); }

		using it = Iterator<Array, T>;
		constexpr it begin() { return it::begin(*this); }
		constexpr it end() { return it::end(*this); }

	private:
		T m_data[N];
	};
}
