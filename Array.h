#pragma once

#include "Iterator.h"

template <typename T, size_t N>
class Array
{
public:
	constexpr Array();
	constexpr bool empty();
	constexpr size_t size() noexcept;
	constexpr T* data() noexcept;
	constexpr const T* data() const noexcept;
	constexpr const T& operator[](const size_t& index) const noexcept;
	constexpr T& operator[](const size_t& index) noexcept;
	constexpr Iterator<T> begin();
	constexpr Iterator<T> end();

private:
	T data_[N];
};

template <typename T, size_t N>
constexpr Array<T, N>::Array() = default;

template <typename T, size_t N>
constexpr bool Array<T, N>::empty()
{
	return N == 0;
}

template <typename T, size_t N>
constexpr size_t Array<T, N>::size() noexcept
{
	return N;
}

template <typename T, size_t N>
constexpr T* Array<T, N>::data() noexcept
{
	return data_;
}

template <typename T, size_t N>
constexpr const T* Array<T, N>::data() const noexcept
{
	return data_;
}

template <typename T, size_t N>
constexpr const T& Array<T, N>::operator[](const size_t& index) const noexcept
{
	return data_[index];
}

template <typename T, size_t N>
constexpr T& Array<T, N>::operator[](const size_t& index) noexcept
{
	return data_[index];
}

template <typename T, size_t N>
constexpr Iterator<T> Array<T, N>::begin()
{
	return Iterator<T>(&data_[0]);
}

template <typename T, size_t N>
constexpr Iterator<T> Array<T, N>::end()
{
	return Iterator<T>(&data_[N]);
}
