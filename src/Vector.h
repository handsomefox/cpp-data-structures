#pragma once

#include "Iterator.h"
#include "pch.h"

#include <cstring>

namespace cpp
{
	template<typename T>
	class Vector
	{
	public:
		// Constructs an empty container, with no elements.
		constexpr Vector() = default;

		// Constructs an empty container, with no elements and required capacity.
		constexpr explicit Vector(const size_t capacity)
			: m_data(Alloc(capacity)), m_capacity(capacity)
		{
		}

		// Constructs a container with a copy of each of the elements in x, in the same order.
		constexpr Vector(const Vector& other)
			: m_data(Alloc(other.m_capacity)), m_size(other.m_size),
			  m_capacity(other.m_capacity)
		{
			Copy(m_data, other.m_data, other.m_size);
		}

		// Constructs a container that acquires the elements of x.
		constexpr Vector(Vector&& other) noexcept
			: m_data(std::move(other.m_data)), m_size(std::move(other.m_size)),
			  m_capacity(std::move(other.m_capacity))
		{
		}

		// Constructs a container with a copy of each of the elements in il, in the same order.
		constexpr Vector(const std::initializer_list<T>& list)
			: m_data(Alloc(list.size())), m_size(list.size()),
			  m_capacity(m_size)
		{
			std::copy(list.begin(), list.end(), m_data);
		}

		// Destroys the container object.
		~Vector()
		{
			Dealloc(m_data);
		}

		// Returns a reference to the element at position n in the vector.
		[[nodiscard]] constexpr T& at(size_t index)
		{
			if (index > m_size)
				throw std::out_of_range("Vector subscript out of range");
			return m_data[index];
		}

		// Returns a reference to the element at position n in the vector.
		[[nodiscard]] constexpr const T& at(size_t index) const
		{
			if (index > m_size)
				throw std::out_of_range("Vector subscript out of range");
			return m_data[index];
		}

		// Returns a reference to the element at position n in the vector container.
		[[nodiscard]] constexpr T& operator[](size_t index)
		{
			return m_data[index];
		}

		// Returns a reference to the element at position n in the vector container.
		[[nodiscard]] constexpr const T& operator[](size_t index) const
		{
			return m_data[index];
		}

		// Returns a reference to the first element in the vector.
		[[nodiscard]] constexpr T& front()
		{
			return m_data[0];
		}

		// Returns a reference to the first element in the vector.
		[[nodiscard]] constexpr T& front() const
		{
			return m_data[0];
		}

		// Returns a reference to the last element in the vector.
		[[nodiscard]] constexpr T& back()
		{
			return m_data[m_size];
		}

		// Returns a reference to the last element in the vector.
		[[nodiscard]] constexpr T& back() const
		{
			return m_data[m_size];
		}

		// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
		[[nodiscard]] constexpr T* data()
		{
			return m_data;
		}

		// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
		[[nodiscard]] constexpr const T* data() const noexcept
		{
			return m_data;
		}

		// Returns whether the vector is empty (i.e. whether its size is 0).
		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return begin() == end();
		}

		// Returns the number of elements in the vector.
		[[nodiscard]] constexpr size_t size() const noexcept
		{
			return m_size;
		}

		// Returns the maximum number of elements that the vector can hold.
		[[nodiscard]] constexpr size_t max_size()
		{
			return std::distance(begin(), end());
		}

		// Requests that the vector capacity be at least enough to contain n elements.
		constexpr void reserve(const size_t new_capacity)
		{
			if (new_capacity > m_capacity)
			{
				auto new_block = Alloc(new_capacity);
				Move(new_block, m_data, m_size);

				Dealloc(m_data);
				m_data = new_block;
				m_capacity = new_capacity;
			}
		}

		// Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		[[nodiscard]] constexpr size_t capacity() const noexcept
		{
			return m_capacity;
		}

		// Requests the container to reduce its capacity to fit its size.
		constexpr void shrink_to_fit()
		{
			if (m_capacity > m_size)
			{
				auto new_block = Alloc(m_size);
				Move(new_block, m_data, m_size);

				Dealloc(m_data);
				m_data = new_block;
				m_capacity = m_size;
			}
		}

		// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		constexpr void clear() noexcept
		{
			std::for_each(begin(), end(), Destroy);
			m_size = 0;
		}

		// Adds a new element at the end of the vector, after its current last element. The content of val is copied to the new element.
		constexpr void push_back(const T& value)
		{
			reserve(m_size + 1);
			m_data[m_size++] = value;
		}

		// Adds a new element at the end of the vector, after its current last element. The content of val is moved to the new element.
		constexpr void push_back(T&& value)
		{
			reserve(m_size + 1);
			m_data[m_size++] = std::move(value);
		}

		// Inserts a new element at the end of the vector, right after its current last element.
		// This new element is constructed in place using args as the arguments for its constructor.
		template<typename... Args>
		constexpr T& emplace_back(Args&&... args)
		{
			reserve(m_size + 1);
			m_data[m_size] = T(std::forward<Args>(args)...);
			return m_data[m_size++];
		}

		// Removes the last element in the vector, effectively reducing the container size by one.
		constexpr void pop_back()
		{
			Destroy(m_data[m_size--]);
		}

		// Resizes the container so that it contains n elements.
		// If value is not specified, the default constructor is used instead.
		constexpr void resize(const size_t count, const T& value = {})
		{
			auto new_block = Alloc(count);

			if (count > m_size)
			{
				Move(new_block, m_data, m_size);

				for (size_t i = m_size; i < count; ++i)
					new_block[i] = Construct(value);
			}
			else
				Move(new_block, m_data, count);

			Dealloc(m_data);

			m_data = new_block;
			m_size = count;
			m_capacity = count;
		}

		// Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		constexpr void swap(Vector& other) noexcept
		{
			std::swap(this->m_data, other.m_data);
		}

		// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		constexpr Vector& operator=(Vector&& other) noexcept
		{
			if (this == &other)
				return *this;

			Dealloc(m_data);
			m_data = std::move(other.m_data);
			m_size = std::move(other.m_size);
			m_capacity = std::move(other.m_capacity);

			return *this;
		}

		// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
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

		[[nodiscard]] It begin()
		{
			return It::begin(*this);
		}

		[[nodiscard]] ConstIterator end() const
		{
			return ConstIterator::end(*this);
		}

		[[nodiscard]] It end()
		{
			return It::end(*this);
		}

	private:
		T* m_data = nullptr;
		size_t m_size = 0;
		size_t m_capacity = 0;

	private:
		inline static void Move(T* dest, T* src, const size_t count)
		{
			if constexpr (std::is_trivial_v<T>)
				memmove_s(dest, count * sizeof(T), src, count * sizeof(T));

			for (size_t i = 0; i < count; ++i)
			{
				if (dest <= src)
					new (&dest[i]) T(std::move(src[i]));
				else
					new (&dest[count - i - 1]) T(std::move(src[count - i - 1]));
			}
		}

		inline static void Copy(T* dest, const T* src, const size_t count)
		{
			if constexpr (std::is_trivial_v<T>)
				memcpy_s(dest, count * sizeof(T), src, count * sizeof(T));

			for (size_t i = 0; i < count; ++i)
			{
				if (dest <= src)
					new (&dest[i]) T(src[i]);
				else
					new (&dest[count - i - 1]) T(src[count - i - 1]);
			}
		}

		inline constexpr static T* Alloc(const size_t size)
		{
			auto mem = new T[size * sizeof(T)];
			return mem;
		}

		inline constexpr static void Dealloc(const T* p)
		{
			delete[] p;
		}

		inline constexpr static void Destroy(const T& p)
		{
			p.~T();
		}

		inline constexpr static T Construct()
		{
			return T{};
		}

		inline constexpr static T Construct(const T& value)
		{
			return T{value};
		}
	};
}// namespace cpp
