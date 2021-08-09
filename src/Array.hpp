#pragma once
#include <initializer_list>

#include <Iterator.hpp>
#ifdef container_type
#undef container_type
#define container_type Array
#endif

template <typename T, size_t N>
class Array
{
public:
	constexpr Array() = default;
	constexpr Array(const std::initializer_list<T>& list)
	{
		size_t count = 0;

		for (auto const& element : list)
		{
			data_[count] = element;
			++count;
		}
	}
	constexpr bool empty()
	{
		return N == 0;
	}
	constexpr size_t size() noexcept
	{
		return N;
	}

	constexpr T* data() noexcept
	{
		return data_;
	}
	constexpr Iterator begin()
	{
		return Iterator(&data_[0]);
	}
	constexpr Iterator end()
	{
		return Iterator(&data_[N]);
	}

	[[nodiscard]] constexpr const T* data() const noexcept
	{
		return data_;
	}

	constexpr const T& operator[](const size_t& index) const noexcept
	{
		return data_[index];
	}
	constexpr T& operator[](const size_t& index) noexcept
	{
		return data_[index];
	}

private:
	T data_[N]{};
};
