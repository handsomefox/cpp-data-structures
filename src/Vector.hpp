#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

namespace mango
{
	template <typename Vector>
	struct VecIter
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = Vector;
		using difference_type = std::ptrdiff_t;
		using pointer = Vector*;
		using reference = Vector&;

		VecIter(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		VecIter& operator++()
		{
			++m_ptr;
			return *this;
		}
		VecIter operator++(Vector)
		{
			VecIter tmp = *this;
			++(*this);
			return tmp;
		}

		friend bool operator==(const VecIter& a, const VecIter& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const VecIter& a, const VecIter& b) { return a.m_ptr != b.m_ptr; }

	private:
		pointer m_ptr = nullptr;
	};

	template <typename T>
	class Vector
	{
	public:
		Vector() { reserve(2); }

		explicit Vector(const size_t capacity) { reserve(capacity); }

		Vector(const Vector& vec)
		{
			size_ = vec.size_;
			capacity_ = vec.capacity_;

			data_ = new T[sizeof & vec.data_];
			memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);
		}

		Vector(Vector&& vec) noexcept
		{
			size_ = vec.size_;
			capacity_ = vec.capacity_;
			data_ = std::move(vec.data_);
		}

		~Vector() { delete[] data_; }

		T& front() { return data_[0]; }

		T& back() { return data_[size_ - 1]; }

		T* data() { return data_; }

		void reserve(const size_t new_capacity)
		{
			capacity_ += new_capacity;
			T* newData = new T[capacity_];

			for (size_t i = 0; i < size_; ++i)
				newData[i] = data_[i];

			delete[] data_;
			data_ = newData;
		}

		[[nodiscard]] bool empty() const { return size_ == 0 ? true : false; }

		size_t size() { return size_; }
		[[nodiscard]] size_t size() const { return size_; }

		size_t capacity() { return capacity_; }
		[[nodiscard]] size_t capacity() const { return capacity_; }

		void clear()
		{
			for (size_t i = 0; i < size_; ++i)
				data_[i].~T();
			size_ = 0;
		}

		void push_back(T data)
		{
			if (size_ >= capacity_)
				reserve(capacity_ + capacity_ / 2);

			data_[size_++] = data;
		}

		template <typename... Args>
		T& emplace_back(Args &&...args)
		{
			if (size_ >= capacity_)
				reserve(capacity_ + capacity_ / 2);

			data_[size_] = T(std::forward<Args>(args)...);
			return data_[size_++];
		}

		void pop_back()
		{
			if (size_ > 0)
			{
				size_--;
				data_[size_].~T();
			}
		}

		void resize(const size_t size)
		{
			T* newData = new T[size];

			for (size_t i = 0; i < size; ++i)
			{
				if (i < size_)
					newData[i] = data_[i];
				else if (std::is_integral_v<T>)
					newData[i] = static_cast<T>(0);
			}
			delete[] data_;

			size_ = size;
			capacity_ = size;
			data_ = newData;
		}

		void print()
		{
			std::cout << "Printing Vector: \n";
			for (size_t i = 0; i < size_; ++i)
				std::cout << data_[i] << "\n";
		}

		const T& operator[](size_t index) const { return data_[index]; }

		constexpr T& operator[](size_t index) { return data_[index]; }

		constexpr Vector& operator=(const Vector& vec)
		{
			if (this == &vec)
				return *this;

			this->size_ = vec.size_;
			this->capacity_ = vec.capacity_;

			data_ = new T[sizeof & vec.data_];
			memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);

			return *this;
		}

		constexpr Vector& operator=(Vector&& vec) noexcept
		{
			if (this == &vec)
				return *this;

			size_ = vec.size_;
			capacity_ = vec.capacity_;

			data_ = vec.data_;

			return *this;
		}
		VecIter<T> begin()
		{
			return VecIter<T>(&data_[0]);
		}
		VecIter<T> end()
		{
			return VecIter<T>(&data_[size_]);
		}

	private:
		T* data_ = nullptr;

		size_t size_ = 0;
		size_t capacity_ = 0;
	};
} // namespace mango
#endif // VECTOR_HPP
