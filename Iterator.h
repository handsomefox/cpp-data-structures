#pragma once

template <typename T>
class Iterator
{
public:
	explicit Iterator(T* ptr);
	T& operator*() const;
	T* operator->();
	Iterator& operator++();
	Iterator operator++(T);

	friend bool operator==(const Iterator<T>& lhs, const Iterator<T>& rhs)
	{
		return lhs.m_ptr == rhs.m_ptr;
	}

	friend bool operator!=(const Iterator<T>& lhs, const Iterator<T>& rhs)
	{
		return lhs.m_ptr != rhs.m_ptr;
	}


private:
	T* m_ptr = nullptr;
};

template <typename T>
Iterator<T>::Iterator(T* ptr) : m_ptr(ptr)
{
}

template <typename T>
T& Iterator<T>::operator*() const
{
	return *m_ptr;
}

template <typename T>
T* Iterator<T>::operator->()
{
	return m_ptr;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
	++m_ptr;
	return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(T)
{
	Iterator tmp = *this;
	++* this;
	return tmp;
}

