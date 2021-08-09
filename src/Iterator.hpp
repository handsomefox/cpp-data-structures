#pragma once

#define container_type char

class Iterator
{
public:
	constexpr explicit Iterator(container_type* ptr) : m_ptr(ptr)
	{
		
	}
	constexpr container_type& operator*() const
	{
		return *m_ptr;
	}
	constexpr container_type* operator->() const
	{
		return m_ptr;
	}
	constexpr Iterator& operator++()
	{
		++m_ptr;
		return *this;
	}
	constexpr Iterator operator++(int)
	{
		const Iterator tmp = *this;
		++* this;
		return tmp;
	}

	constexpr friend bool operator==(const Iterator lhs, const Iterator rhs)
	{
		return lhs.m_ptr == rhs.m_ptr;
	}

	constexpr friend bool operator!=(const Iterator lhs, const Iterator rhs)
	{
		return lhs.m_ptr != rhs.m_ptr;
	}

private:
	container_type* m_ptr = nullptr;
};
