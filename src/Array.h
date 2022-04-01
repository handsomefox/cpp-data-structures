#pragma once

#include "pch.h"

#include "Iterator.h"

namespace cpp
{
	template<typename T, size_t N>
	class Array
	{
	public:
		// initializes the array
		constexpr Array() = default;
		// destroys the array
		constexpr ~Array() = default;

		// Initializes the array using the given std::initializer_list
		constexpr Array(const std::initializer_list<T>& list)
		{
			size_t count = 0;
			for (auto const& element : list)
			{
				if (count >= N)
					return;

				m_data[count] = element;
				++count;
			}
		}

		// Returns the number of elements in the array container.
		//
		// The size of an array object is always equal to the second template
		// parameter used to instantiate the array template class (N).
		constexpr size_t size() noexcept
		{
			return N;
		}

		// Returns the maximum number of elements that the array container can hold.
		// The max_size of an array object, just like its size, is always equal to
		// the second template parameter used to instantiate the array template class.
		constexpr size_t max_size() noexcept
		{
			return N;
		}

		// Returns a reference to the element at position n in the array container.
		constexpr T& operator[](const size_t& index) noexcept
		{
			return m_data[index];
		}

		// Returns a reference to the element at position n in the array container.
		constexpr const T& operator[](const size_t& index) const noexcept
		{
			if (index >= N)
			{
				throw std::out_of_range("Index out of range");
			}

			return m_data[index];
		}

		// Returns a reference to the element at position n in the array.
		[[nodiscard]] constexpr const T& at(size_t index) const
		{
			if (index >= N)
			{
				throw std::out_of_range("Index out of range");
			}

			return m_data[index];
		}

		// Returns a reference to the element at position n in the array.
		constexpr T& at(size_t index)
		{
			return m_data[index];
		}

		// Returns a reference to the first element in the array container.
		[[nodiscard]] constexpr const T& front() const
		{
			return m_data[0];
		}

		// Returns a reference to the first element in the array container.
		constexpr T& front()
		{
			return m_data[0];
		}

		// Returns a reference to the last element in the array container.
		[[nodiscard]] constexpr const T& back() const
		{
			return m_data[N - 1];
		}

		// Returns a reference to the last element in the array container.
		constexpr T& back()
		{
			return m_data[N];
		}

		// Returns a pointer to the first element in the array object.
		constexpr T* data() noexcept
		{
			return m_data;
		}

		// Returns a pointer to the first element in the array object.
		[[nodiscard]] constexpr const T* data() const noexcept
		{
			return m_data;
		}

		// Returns a bool value indicating whether the array container is empty, i.e. whether its size is 0.
		constexpr bool empty() noexcept
		{
			return N == 0;
		}

		// Sets val as the val for all the elements in the array object.
		void fill(const T& val)
		{
			std::fill(begin(), end(), val);
		}

		using it = Iterator<Array, T>;

		constexpr it begin()
		{
			return it::begin(*this);
		}

		constexpr it end()
		{
			return it::end(*this);
		}

	private:
		T m_data[N];
	};
}// namespace cpp
