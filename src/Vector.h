#pragma once

#include "Iterator.h"
#include "VectorHelpers.h"
#include "pch.h"

namespace cpp
{

	template<typename T>
	class Vector
	{
	 public:
		constexpr Vector() = default;

		constexpr explicit Vector(const size_t capacity)
			: m_data(VectorHelpers<T>::Alloc(capacity)), m_capacity(capacity)
		{
		}

		constexpr Vector(const Vector& other)
			: m_data(VectorHelpers<T>::Alloc(other.m_capacity)), m_size(other.m_size),
			  m_capacity(other.m_capacity)
		{
			VectorHelpers<T>::Copy(m_data, other.m_data, other.m_size);
		}

		constexpr Vector(Vector&& other) noexcept
			: m_data(std::move(other.m_data)), m_size(std::move(other.m_size)),
			  m_capacity(std::move(other.m_capacity))
		{
		}

		constexpr Vector(const std::initializer_list<T>& list)
			: m_data(VectorHelpers<T>::Alloc(list.size())), m_size(list.size()),
			  m_capacity(m_size)
		{
			std::copy(list.begin(), list.end(), m_data);
		}

		~Vector()
		{
			VectorHelpers<T>::Dealloc(m_data);
		}

		constexpr T& at(size_t index)
		{
			if (index > m_size)
				throw std::out_of_range("Vector subscript out of range");
			return m_data[index];
		}

		[[nodiscard]] constexpr const T& at(size_t index) const
		{
			if (index > m_size)
				throw std::out_of_range("Vector subscript out of range");
			return m_data[index];
		}

		constexpr T& operator[](size_t index)
		{
			return m_data[index];
		}

		constexpr const T& operator[](size_t index) const
		{
			return m_data[index];
		}

		constexpr T& front()
		{
			return m_data[0];
		}

		[[nodiscard]] constexpr T& front() const
		{
			return m_data[0];
		}

		constexpr T& back()
		{
			return m_data[m_size];
		}

		[[nodiscard]] constexpr T& back() const
		{
			return m_data[m_size];
		}

		constexpr T* data()
		{
			return m_data;
		}

		[[nodiscard]] constexpr const T* data() const noexcept
		{
			return m_data;
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return begin() == end();
		}

		[[nodiscard]] constexpr size_t size() const noexcept
		{
			return m_size;
		}

		constexpr size_t max_size()
		{
			return std::distance(begin(), end());
		}

		constexpr void reserve(const size_t new_capacity)
		{
			if (new_capacity > m_capacity)
			{
				auto new_block = VectorHelpers<T>::Alloc(new_capacity);
				VectorHelpers<T>::Move(new_block, m_data, m_size);

				VectorHelpers<T>::Dealloc(m_data);
				m_data = new_block;
				m_capacity = new_capacity;
			}
		}

		[[nodiscard]] constexpr size_t capacity() const noexcept
		{
			return m_capacity;
		}

		constexpr void shrink_to_fit()
		{
			if (m_capacity > m_size)
			{
				auto new_block = VectorHelpers<T>::Alloc(m_size);
				VectorHelpers<T>::Move(new_block, m_data, m_size);

				VectorHelpers<T>::Dealloc(m_data);
				m_data = new_block;
				m_capacity = m_size;
			}
		}

		constexpr void clear() noexcept
		{
			std::for_each(begin(), end(), VectorHelpers<T>::Destroy);
			m_size = 0;
		}

		constexpr void push_back(const T& value)
		{
			reserve(m_size + 1);
			m_data[m_size++] = value;
		}

		constexpr void push_back(T&& value)
		{
			reserve(m_size + 1);
			m_data[m_size++] = std::move(value);
		}

		template<typename... Args>
		constexpr T& emplace_back(Args&& ...args)
		{
			reserve(m_size + 1);
			m_data[m_size] = T(std::forward<Args>(args)...);
			return m_data[m_size++];
		}

		constexpr void pop_back()
		{
			VectorHelpers<T>::Destroy(m_data[m_size--]);
		}

		constexpr void resize(const size_t count)
		{
			auto new_block = VectorHelpers<T>::Alloc(count);
			if (count > m_size)
			{
				VectorHelpers<T>::Move(new_block, m_data, m_size);
				for (size_t i = m_size; i < count; ++i)
					new_block[i] = VectorHelpers<T>::Construct();
			}
			else
				VectorHelpers<T>::Move(new_block, m_data, count);

			VectorHelpers<T>::Dealloc(m_data);

			m_data = std::move(new_block);
			m_size = count;
			m_capacity = count;
		}

		constexpr void resize(const size_t count, const T& value)
		{
			auto new_block = VectorHelpers<T>::Alloc(count);

			if (count > m_size)
			{
				VectorHelpers<T>::Move(new_block, m_data, m_size);

				for (size_t i = m_size; i < count; ++i)
					new_block[i] = VectorHelpers<T>::Construct(value);
			}
			else
				VectorHelpers<T>::Move(new_block, m_data, count);

			VectorHelpers<T>::Dealloc(m_data);

			m_data = new_block;
			m_size = count;
			m_capacity = count;
		}

		constexpr void swap(Vector& other) noexcept
		{
			std::swap(this->m_data, other.m_data);
		}

		constexpr Vector& operator=(Vector&& other) noexcept
		{
			if (this == &other)
				return *this;

			VectorHelpers<T>::Dealloc(m_data);
			m_data = std::move(other.m_data);
			m_size = std::move(other.m_size);
			m_capacity = std::move(other.m_capacity);

			return *this;
		}

		constexpr Vector& operator=(const Vector& other)
		{
			if (this == &other)
				return *this;

			reserve(other.m_capacity);
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			std::copy(other.begin(), other.end(), m_data);

			return *this;
		}

		using ConstIterator = Iterator<Vector const, T const>;
		using It = Iterator<Vector, T>;

		[[nodiscard]] ConstIterator begin() const
		{
			return ConstIterator::begin(*this);
		}

		It begin()
		{
			return It::begin(*this);
		}

		[[nodiscard]] ConstIterator end() const
		{
			return ConstIterator::end(*this);
		}

		It end()
		{
			return It::end(*this);
		}

	 private:
		T* m_data = nullptr;
		size_t m_size = 0;
		size_t m_capacity = 0;
	};
}// namespace cpp
