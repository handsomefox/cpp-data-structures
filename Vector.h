#pragma once
#include <iostream>

#include "Iterator.h"
template <typename T>
class Vector
{
public:
	Vector();
	explicit Vector(const size_t capacity);
	Vector(const Vector& vec);
	Vector(Vector&& vec) noexcept;
	~Vector();
	T& front();
	T& back();
	T* data();
	void reserve(const size_t new_capacity);
	bool empty() const;
	size_t size();
	size_t size() const;
	size_t capacity();
	size_t capacity() const;
	void clear();
	void push_back(T data);
	template <typename... Args>
	T& emplace_back(Args&&...args);
	void pop_back();
	void resize(const size_t size);
	void print();
	const T& operator[](size_t index) const;
	constexpr T& operator[](size_t index);
	constexpr Vector& operator=(const Vector& vec);
	constexpr Vector& operator=(Vector&& vec) noexcept;
	Iterator<T> begin();
	Iterator<T> end();

private:
	T* data_ = nullptr;

	size_t size_ = 0;
	size_t capacity_ = 0;
};

template <typename T>
Vector<T>::Vector()
{
	reserve(2);
}

template <typename T>
Vector<T>::Vector(const size_t capacity)
{
	reserve(capacity);
}

template <typename T>
Vector<T>::Vector(const Vector& vec)
{
	size_ = vec.size_;
	capacity_ = vec.capacity_;

	data_ = new T[sizeof & vec.data_];
	memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);
}

template <typename T>
Vector<T>::Vector(Vector&& vec) noexcept
{
	size_ = vec.size_;
	capacity_ = vec.capacity_;
	data_ = std::move(vec.data_);
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] data_;
}

template <typename T>
T& Vector<T>::front()
{
	return data_[0];
}

template <typename T>
T& Vector<T>::back()
{
	return data_[size_ - 1];
}

template <typename T>
T* Vector<T>::data()
{
	return data_;
}

template <typename T>
void Vector<T>::reserve(const size_t new_capacity)
{
	capacity_ += new_capacity;
	T* newData = new T[capacity_];

	for (size_t i = 0; i < size_; ++i)
	{
		newData[i] = data_[i];
	}

	delete[] data_;
	data_ = newData;
}

template <typename T>
bool Vector<T>::empty() const
{
	return size_ == 0 ? true : false;
}

template <typename T>
size_t Vector<T>::size()
{
	return size_;
}

template <typename T>
size_t Vector<T>::size() const
{
	return size_;
}

template <typename T>
size_t Vector<T>::capacity()
{
	return capacity_;
}

template <typename T>
size_t Vector<T>::capacity() const
{
	return capacity_;
}

template <typename T>
void Vector<T>::clear()
{
	for (size_t i = 0; i < size_; ++i)
	{
		data_[i].~T();
	}
	size_ = 0;
}

template <typename T>
void Vector<T>::push_back(T data)
{
	if (size_ >= capacity_)
	{
		reserve(capacity_ + capacity_ / 2);
	}

	data_[size_++] = data;
}

template <typename T>
template <typename ... Args>
T& Vector<T>::emplace_back(Args&&... args)
{
	if (size_ >= capacity_)
	{
		reserve(capacity_ + capacity_ / 2);
	}

	data_[size_] = T(std::forward<Args>(args)...);
	return data_[size_++];
}

template <typename T>
void Vector<T>::pop_back()
{
	if (size_ > 0)
	{
		size_--;
		data_[size_].~T();
	}
}

template <typename T>
void Vector<T>::resize(const size_t size)
{
	T* newData = new T[size];

	for (size_t i = 0; i < size; ++i)
	{
		if (i < size_)
		{
			newData[i] = data_[i];
		}
		else if (std::is_integral_v<T>)
		{
			newData[i] = static_cast<T>(0);
		}
	}
	delete[] data_;

	size_ = size;
	capacity_ = size;
	data_ = newData;
}

template <typename T>
void Vector<T>::print()
{
	std::cout << "Printing Vector: \n";
	for (size_t i = 0; i < size_; ++i)
	{
		std::cout << data_[i] << "\n";
	}
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return data_[index];
}

template <typename T>
constexpr T& Vector<T>::operator[](size_t index)
{
	return data_[index];
}

template <typename T>
constexpr Vector<T>& Vector<T>::operator=(const Vector& vec)
{
	if (this == &vec)
	{
		return *this;
	}

	this->size_ = vec.size_;
	this->capacity_ = vec.capacity_;

	data_ = new T[sizeof & vec.data_];
	memcpy_s(data_, sizeof data_, vec.data_, sizeof vec.data_);

	return *this;
}

template <typename T>
constexpr Vector<T>& Vector<T>::operator=(Vector&& vec) noexcept
{
	if (this == &vec)
	{
		return *this;
	}

	size_ = vec.size_;
	capacity_ = vec.capacity_;

	data_ = vec.data_;

	return *this;
}

template <typename T>
Iterator<T> Vector<T>::begin()
{
	return Iterator<T>(&data_[0]);
}

template <typename T>
Iterator<T> Vector<T>::end()
{
	return Iterator<T>(&data_[size_]);
}
