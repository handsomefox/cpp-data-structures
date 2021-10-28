#pragma once

namespace cpp
{
	template<typename Container, typename ValueType>
	class Iterator
	{
	public:
		friend Container;

		constexpr Iterator(const Iterator& obj) = default;

		constexpr Iterator operator++()
		{
			++m_index;
			return *this;
		}
		constexpr Iterator operator++(int)
		{
			++m_index;
			return Iterator{ m_container, m_index - 1 };
		}
		constexpr Iterator operator--()
		{
			--m_index;
			return *this;
		}
		constexpr Iterator operator--(int)
		{
			++m_index;
			return Iterator{ m_container, m_index + 1 };
		}

		constexpr ValueType& operator*() { return m_container[m_index]; }
		constexpr const ValueType& operator*() const { return m_container[m_index]; }

		constexpr ValueType* operator->() { return &m_container[m_index]; }
		constexpr const ValueType* operator->() const { return &m_container[m_index]; }

		constexpr bool operator==(Iterator other) const { return m_index == other.m_index; }
		constexpr bool operator!=(Iterator other) const { return m_index != other.m_index; }
		constexpr bool operator<(Iterator other) const { return m_index < other.m_index; }
		constexpr bool operator>(Iterator other) const { return m_index > other.m_index; }
		constexpr bool operator<=(Iterator other) const { return m_index <= other.m_index; }
		constexpr bool operator>=(Iterator other) const { return m_index >= other.m_index; }

		Iterator& operator=(const Iterator& other)
		{
			m_index = other.m_index;
			return *this;
		}

	private:
		static constexpr Iterator begin(Container& container) { return { container, 0 }; }
		static constexpr Iterator end(Container& container)
		{
			return { container, container.size() };
		}

		constexpr Iterator(Container& container, const size_t index)
			: m_container(container)
			, m_index(index)
		{
		}

		Container& m_container;
		size_t m_index;
	};
};
