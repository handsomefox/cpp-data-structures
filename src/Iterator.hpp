#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace mango {
	template <typename container_type>
	struct Iter
	{
		using iterator_category = std::forward_iterator_tag;
		using value_type = container_type;
		using difference_type = std::ptrdiff_t;
		using pointer = container_type*;
		using reference = container_type&;

		Iter(pointer ptr) : m_ptr(ptr)
		{
		}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		Iter& operator++()
		{
			++m_ptr;
			return *this;
		}

		Iter operator++(container_type)
			{
			Iter tmp = *this;
			++*this;
			return tmp;
		}

		friend bool operator==(const Iter& a, const Iter& b) { return a.m_ptr == b.m_ptr; }
		friend bool operator!=(const Iter& a, const Iter& b) { return a.m_ptr != b.m_ptr; }

	private:
		pointer m_ptr = nullptr;
	};

} // namespace mango
#endif // ITERATOR_HPP