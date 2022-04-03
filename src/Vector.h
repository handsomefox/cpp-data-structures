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

		// Constructs an empty container, with no elements and required cap.
		constexpr explicit Vector(const size_t capacity)
			: _data({new T[capacity], 0, capacity})
		{
		}

		// Constructs a container with a copy of each of the elements in x, in the same order.
		constexpr Vector(const Vector& other)
		{
			this->reserve(other.capacity());

			for (auto const& e : other)
				this->push_back(e);
		}

		// Constructs a container that acquires the elements of x.
		constexpr Vector(Vector&& other) noexcept
			: _data(std::move(other._data))
		{
		}

		// Constructs a container with a copy of each of the elements in il, in the same order.
		constexpr Vector(const std::initializer_list<T>& list)
		{
			auto const& list_data = std::data(list);
			const auto list_size = list.size();

			_data = {new T[list_size], list_size, list_size};

			for (size_t i = 0; i < list_size; ++i)
				_data.p[i] = list_data[i];
		}

		// Destroys the container object.
		~Vector()
		{
			delete[] _data.p;
		}

		// Returns a reference to the element at position n in the vector.
		constexpr T& at(size_t index)
		{
			if (index > _data.sz)
				throw std::out_of_range("Vector subscript out of range");
			return _data.p[index];
		}

		// Returns a reference to the element at position n in the vector.
		constexpr const T& at(size_t index) const
		{
			if (index > _data.sz)
				throw std::out_of_range("Vector subscript out of range");
			return _data.p[index];
		}

		// Returns a reference to the element at position n in the vector container.
		constexpr T& operator[](size_t index)
		{
			return _data.p[index];
		}

		// Returns a reference to the element at position n in the vector container.
		constexpr const T& operator[](size_t index) const
		{
			return _data.p[index];
		}

		// Returns a reference to the first element in the vector.
		constexpr T& front()
		{
			return _data.p[0];
		}

		// Returns a reference to the first element in the vector.
		constexpr T& front() const
		{
			return _data.p[0];
		}

		// Returns a reference to the last element in the vector.
		constexpr T& back()
		{
			return _data.p[_data.sz - 1];
		}

		// Returns a reference to the last element in the vector.
		constexpr T& back() const
		{
			return _data.p[_data.sz - 1];
		}

		// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
		constexpr T* data()
		{
			return _data.p;
		}

		// Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
		constexpr const T* data() const noexcept
		{
			return _data.p;
		}

		// Returns whether the vector is empty (i.e. whether its size is 0).
		constexpr bool empty() const noexcept
		{
			return begin() == end();
		}

		// Returns the number of elements in the vector.
		constexpr size_t size() const noexcept
		{
			return _data.sz;
		}

		// Returns the maximum number of elements that the vector can hold.
		constexpr size_t max_size()
		{
			return std::distance(begin(), end());
		}

		// Requests that the vector cap be at least enough to contain n elements.
		constexpr void reserve(const size_t new_capacity)
		{
			if (_data.cap > new_capacity)
				return;

			auto block = new T[new_capacity];

			for (size_t i = 0; i < _data.sz; ++i)
				block[i] = std::move(_data.p[i]);

			delete[] _data.p;
			_data = {block, _data.sz, new_capacity};
		}

		// Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		constexpr size_t capacity() const noexcept
		{
			return _data.cap;
		}

		// Requests the container to reduce its cap to fit its size.
		constexpr void shrink_to_fit()
		{
			if (_data.cap < _data.sz)
				return;

			auto block = new T[_data.sz];
			for (size_t i = 0; i < _data.sz; ++i)
				block[i] = std::move(_data.p[i]);

			delete[] _data.p;
			_data = {block, _data.sz, _data.sz};
		}

		// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		constexpr void clear() noexcept
		{
			std::for_each(begin(), end(), [&](T& t) {
				t.~T();
			});
			_data.sz = 0;
		}

		// Adds a new element at the end of the vector, after its current last element. The content of val is copied to the new element.
		constexpr void push_back(const T& value)
		{
			if (_data.cap == _data.sz)
				reserve(1 + _data.sz * 2);

			_data.p[_data.sz++] = value;
		}

		// Adds a new element at the end of the vector, after its current last element. The content of val is moved to the new element.
		constexpr void push_back(T&& value)
		{
			if (_data.cap == _data.sz)
				reserve(1 + _data.sz * 2);

			_data.p[_data.sz++] = std::move(value);
		}

		// Inserts a new element at the end of the vector, right after its current last element.
		// This new element is constructed in place using args as the arguments for its constructor.
		template<typename... Args>
		constexpr T& emplace_back(Args&&... args)
		{
			if (_data.cap == _data.sz)
				reserve(1 + _data.sz * 2);

			_data.p[_data.sz] = T(std::forward<Args>(args)...);
			return _data.p[_data.sz++];
		}

		// Removes the last element in the vector, effectively reducing the container size by one.
		constexpr void pop_back()
		{
			_data.p[_data.sz--].~T();
		}

		// Resizes the container so that it contains n elements.
		// If value is not specified, the default constructor is used instead.
		constexpr void resize(const size_t count, const T& value = {})
		{
			if (count == _data.sz)
				return;

			auto buffer = new T[count];

			if (count > _data.sz)
			{
				for (size_t i = 0; i < _data.sz; ++i)
					buffer[i] = std::move(_data.p[i]);

				for (size_t i = _data.sz; i < count; ++i)
					buffer[i] = value;
			}
			else
			{
				for (size_t i = 0; i < count; ++i)
					buffer[i] = std::move(_data.p[i]);
			}

			delete[] _data.p;

			_data = {buffer, count, count};
		}

		// Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		constexpr void swap(Vector& other) noexcept
		{
			std::swap(this->_data, other._data);
		}

		// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		constexpr Vector& operator=(Vector&& other) noexcept
		{
			if (this == &other)
				return *this;

			delete[] _data.p;

			_data = std::move(other._data);
			return *this;
		}

		// Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		constexpr Vector& operator=(const Vector& other)
		{
			if (this == &other)
				return *this;

			reserve(other.m_capacity);
			_data.sz = other.m_size;
			_data.cap = other.m_capacity;

			std::copy(other.begin(), other.end(), _data.p);

			return *this;
		}

		using ConstIterator = Iterator<Vector const, T const>;
		using It = Iterator<Vector, T>;

		ConstIterator begin() const
		{
			return ConstIterator::begin(*this);
		}

		It begin()
		{
			return It::begin(*this);
		}

		ConstIterator end() const
		{
			return ConstIterator::end(*this);
		}

		It end()
		{
			return It::end(*this);
		}

	private:
		struct VectorData {
			T* p = nullptr;
			size_t sz = 0;
			size_t cap = 0;
		};
		VectorData _data{};
	};
}// namespace cpp
