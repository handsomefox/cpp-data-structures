#pragma once

#include <utility>
#include <stdexcept>

namespace cpp {
	template <typename Vector>
	class VectorIterator
	{
	public:
		using ValueType = typename Vector::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	public:
		VectorIterator(PointerType ptr)
			: m_ptr(ptr) {}

		VectorIterator& operator++()
		{
			++m_ptr;
			return (*this);
		}

		VectorIterator& operator++(int)
		{
			auto iterator = *this;
			++m_ptr;
			return iterator;
		}

		VectorIterator& operator--()
		{
			--m_ptr;
			return (*this);
		}

		VectorIterator& operator--(int)
		{
			auto iterator = *this;
			--m_ptr;
			return iterator;
		}

		ReferenceType operator[](size_t index) { return *(m_ptr + index); }

		PointerType operator->() { return m_ptr; }

		ReferenceType operator*() { return *m_ptr; }

		bool operator==(const VectorIterator& other) const { return this->m_ptr == other.m_ptr; }
		bool operator!=(const VectorIterator& other) const { return this->m_ptr != other.m_ptr; }

	private:
		PointerType m_ptr;
	};
	template<typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Iterator = VectorIterator<Vector<T>>;

	public:
		constexpr Vector() = default;
		constexpr explicit Vector(const size_t capacity)
		{
			m_data = allocate(capacity);
			m_capacity = capacity;
		}

		constexpr Vector(const Vector& vec)
		{
			m_data = allocate(vec.m_capacity);

			for (size_t i = 0; i < vec.m_size; ++i)
				m_data[i] = vec.m_data[i];

			m_size = vec.m_size;
			m_capacity = vec.m_capacity;
		}
		constexpr Vector(Vector&& vec) noexcept
		{
			m_data = std::move(vec.m_data);
			m_size = std::move(vec.m_size);
			m_capacity = std::move(vec.m_capacity);
		}
		constexpr Vector(const std::initializer_list<T>& list)
		{
			m_size = list.size();
			m_capacity = m_size;

			m_data = allocate(m_size);

			std::copy(list.begin(), list.end(), m_data);
		}

		~Vector() { deallocate(m_data); }
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

		constexpr T& operator[](size_t index) { return m_data[index]; }
		constexpr const T& operator[](size_t index) const { return m_data[index]; }

		constexpr T& front() { return m_data[0]; }
		[[nodiscard]] constexpr T& front() const { return m_data[0]; }
		constexpr T& back() { return m_data[m_size]; }
		[[nodiscard]] constexpr T& back() const { return m_data[m_size]; }

		constexpr T* data() { return m_data; }
		[[nodiscard]] constexpr const T* data() const noexcept { return m_data; }

		Iterator begin() { return Iterator(m_data); }
		[[nodiscard]] constexpr Iterator begin() const { return Iterator(m_data); }
		Iterator end() { return Iterator(m_data + m_size); }
		[[nodiscard]] constexpr Iterator end() const { return Iterator(m_data + m_size); }

		[[nodiscard]] constexpr bool empty() const noexcept { return begin() == end(); }

		[[nodiscard]] constexpr size_t size() const noexcept { return m_size; }

		constexpr size_t max_size() { return std::distance(begin(), end()); }

		constexpr void reserve(const size_t new_capacity)
		{
			if (new_capacity > m_capacity)
			{
				auto new_block = allocate(new_capacity);

				for (size_t i = 0; i < m_size; ++i)
					new_block[i] = std::move(m_data[i]);

				deallocate(m_data);
				m_data = new_block;
				m_capacity = new_capacity;
			}
		}

		[[nodiscard]] constexpr size_t capacity() const noexcept { return m_capacity; }

		constexpr void shrink_to_fit()
		{
			if (m_capacity > m_size)
			{
				auto new_block = allocate(m_size);

				for (size_t i = 0; i < m_size; ++i)
					new_block[i] = std::move(m_data[i]);

				deallocate(m_data);
				m_data = new_block;
				m_capacity = m_size;
			}
		}

		constexpr void clear() noexcept
		{
			for (size_t i = 0; i < m_size; ++i)
				destroy(m_data[i]);
			m_size = 0;
		}

		/*
		 * TODO: Implement insert (https://en.cppreference.com/w/cpp/container/vector/insert)
		 * TODO: Implement emplace (https://en.cppreference.com/w/cpp/container/vector/emplace)
		 * TODO: Implement erase (https://en.cppreference.com/w/cpp/container/vector/erase)
		 */

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
		template< typename... Args >
		constexpr T& emplace_back(Args&&... args)
		{
			reserve(m_size + 1);
			m_data[m_size] = T(std::forward<Args>(args)...);
			return m_data[m_size++];
		}

		constexpr void pop_back() { destroy(m_data[m_size--]); }

		constexpr void resize(const size_t count)
		{
			auto new_block = allocate(count);

			if (count > m_size) {
				for (size_t i = 0; i < m_size; ++i)
					new_block[i] = std::move(m_data[i]);

				for (size_t i = m_size; i < count; ++i)
					new_block[i] = T{ };
			}
			else
				for (size_t i = 0; i < count; ++i)
					new_block[i] = std::move(m_data[i]);

			deallocate(m_data);

			m_data = new_block;
			m_size = count;
			m_capacity = count;
		}
		constexpr void resize(const size_t count, const T& value)
		{
			auto new_block = allocate(count);

			if (count > m_size)
			{
				for (size_t i = 0; i < m_size; ++i)
					new_block[i] = std::move(m_data[i]);

				for (size_t i = m_size; i < count; ++i)
					new_block[i] = T{ value };
			}
			else
				for (size_t i = 0; i < count; ++i)
					new_block[i] = std::move(m_data[i]);

			deallocate(m_data);

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
			if (this == &other) return *this;

			reserve(other.m_capacity);
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			for (size_t i = 0; i < m_size; ++i)
				m_data[i] = std::move(other.m_data[i]);

			return *this;
		}

		constexpr Vector& operator=(const Vector& other)
		{
			if (this == &other) return *this;

			reserve(other.m_capacity);
			m_size = other.m_size;
			m_capacity = other.m_capacity;

			for (size_t i = 0; i < m_size; ++i)
				m_data[i] = other.m_data[i];

			return *this;
		}

		//constexpr bool operator==(const Vector& other)
		//{
		//	return std::lexicographical_compare(this.begin(), this.end(), other.begin(), other.end());
		//}
		//constexpr bool operator<=>(const Vector& other)
		//{
		//	return std::lexicographical_compare_three_way(this.begin(), this.end(), other.begin(), other.end());
		//}
	private:
		static T* allocate(const size_t size)
		{
			auto mem = new T[size * sizeof(T)];
			return mem;
		}
		static void deallocate(const T* p)
		{
			delete[] p;
		}

		static void destroy(const T& p)
		{
			p.~T();
		}

		T* m_data = nullptr;
		size_t m_size = 0;
		size_t m_capacity = 0;
	};
}