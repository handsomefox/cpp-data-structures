#pragma once
#include <iostream>

namespace mango
{
	template<typename T>
	class Vector
	{
	public:
		
		Vector();
		explicit Vector(size_t capacity);
		~Vector();

		// Copy

		Vector(const Vector&);
		Vector& operator=(Vector);
		Vector& operator=(const Vector&);
		
		// Move	
		
		Vector(Vector&&) noexcept;
		Vector& operator=(Vector&&) noexcept;

		T& front();
		T& back();
		T* data();
		
		void reserve(size_t new_capacity);
		bool empty() const;
		
		size_t size();
		size_t size() const;
		size_t capacity();
		size_t capacity() const;
		
		void clear();
		void resize(size_t size);

		void push_back(T data);
		template <typename... Args>
		T& emplace_back(Args&&... args);
		void pop_back();
		
		void print();
		
		const T& operator[](size_t index) const;
		T& operator[](size_t index);
	
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
	Vector<T>::~Vector()
	{
		delete[] data_;
	}

	template <typename T>
	Vector<T>::Vector(const Vector&)
	{
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector)
	{
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector&)
	{
	}

	template <typename T>
	Vector<T>::Vector(Vector&&) noexcept
	{
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&&) noexcept
	{
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
		T* newData = new T[new_capacity];

		for (size_t i = 0; i < size_; ++i)
			newData[i] = data_[i];

		delete[] data_;
		data_ = newData;
		capacity_ = new_capacity;
	}

	template <typename T>
	bool Vector<T>::empty() const
	{
		if (size_ == 0) return true;
		return false;
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
			data_[i].~T();
		size_ = 0;
	}

	template <typename T>
	void Vector<T>::push_back(T data)
	{
		if (size_ >= capacity_) { reserve(capacity_ + capacity_ / 2); }
		data_[size_++] = data;
	}

	template <typename T>
	template <typename ... Args>
	T& Vector<T>::emplace_back(Args&&... args)
	{
		if (size_ >= capacity_) { reserve(capacity_ + capacity_ / 2); }

		data_[size_] = T(std::forward<Args>(args)...);

		return data_[size_++];
	}

	template <typename T>
	void Vector<T>::pop_back()
	{
		T* newData = new T[capacity_];
		for (size_t i = 0; i < size_ - 1; ++i)
		{
			newData[i] = data_[i];
		}
		size_ = size_ - 1;
		delete[] data_;
		data_ = newData;
	}

	template <typename T>
	void Vector<T>::resize(const size_t size)
	{
		T* newData = new T[size];

		for (size_t i = 0; i < size; ++i)
		{
			if (i < size_)
				newData[i] = data_[i];
			else if (std::is_integral_v<T>) newData[i] = static_cast<T>(0);
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
			std::cout << data_[i] << "\n";
	}

	template <typename T>
	const T& Vector<T>::operator[](size_t index) const
	{
		return data_[index];
	}

	template <typename T>
	T& Vector<T>::operator[](size_t index)
	{
		return data_[index];
	}

	static void RunVectorTest()
	{
		Vector<int> vec;
		vec.print();
		std::cout << "Empty: " << vec.empty() << "\n";

		std::cout << "Adding data to Vector\n";
		vec.push_back(1);
		vec.emplace_back(2);
		vec.emplace_back(3);
		vec.emplace_back(4);
		vec.print();

		std::cout << "Empty: " << vec.empty() << "\n";

		std::cout << "Back: " << vec.back() << "\n";
		std::cout << "Front: " << vec.front() << "\n";
		std::cout << "Capacity: " << vec.capacity() << "\n";
		std::cout << "Size: " << vec.size() << "\n";

		std::cout << "Pop back\n";
		vec.pop_back();
		vec.print();

		std::cout << "Resize (smaller)\n";
		vec.resize(2);
		vec.print();

		std::cout << "Resize (bigger)\n";
		vec.resize(5);
		vec.print();

		std::cout << "Clear\n";
		vec.clear();

		std::cout << "Print (expected == nothing)\n";
		vec.print();

		std::cout << "Constructing a Vector with capacity of 5\n";
		Vector<std::string> vec2(5);
		std::cout << "Capacity: " << vec2.capacity() << "\n";
		std::cout << "Empty: " << vec2.empty() << "\n";
		std::cout << "Size: " << vec2.size() << "\n";

		std::cout << "Adding data to Vector\n";
		vec2.push_back("Hello");
		vec2.push_back("this");
		vec2.push_back("is");
		vec2.push_back("my Vector!");
		vec2.print();

		std::cout << "Capacity: " << vec2.capacity() << "\n";
		std::cout << "Empty: " << vec2.empty() << "\n";
		std::cout << "Size: " << vec2.size() << "\n";

		std::cout << "Back: " << vec2.back() << "\n";
		std::cout << "Front: " << vec2.front() << "\n";

		std::cout << "Pop back\n";
		vec2.pop_back();
		vec2.print();

		std::cout << "Resize (smaller)\n";
		vec2.resize(1);
		vec2.print();

		std::cout << "Resize (bigger)\n";
		vec2.resize(5);
		vec2.print();

		std::cout << "Clear\n";
		vec2.clear();

		std::cout << "Print (expected == nothing)\n";
		vec2.print();
	}
}