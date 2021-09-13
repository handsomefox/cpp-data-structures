#pragma once

namespace cpp
{
    template <typename Array>
    class ArrayIterator
    {
    public:
        using ValueType = typename Array::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

    public:
        ArrayIterator(PointerType ptr)
            : m_ptr(ptr) {}

        ArrayIterator& operator++()
        {
            ++m_ptr;
            return (*this);
        }

        ArrayIterator& operator++(int)
        {
            auto iterator = *this;
            ++m_ptr;
            return iterator;
        }

        ArrayIterator& operator--()
        {
            --m_ptr;
            return (*this);
        }

        ArrayIterator& operator--(int)
        {
            auto iterator = *this;
            --m_ptr;
            return iterator;
        }

        ReferenceType operator[](size_t index) { return *(m_ptr + index); }

        PointerType operator->() { return m_ptr; }

        ReferenceType operator*() { return *m_ptr; }

        bool operator==(const ArrayIterator& other) const { return this->m_ptr == other.m_ptr; }
        bool operator!=(const ArrayIterator& other) const { return this->m_ptr != other.m_ptr; }

    private:
        PointerType m_ptr;
    };

    template <typename T, size_t N>
    class Array
    {
    public:
        using ValueType = T;
        using Iterator = ArrayIterator<Array<T, N>>;

    public:
        constexpr Array() = default;

        explicit constexpr Array(const std::initializer_list<T>& list)
        {
            size_t count = 0;
            for (auto const& element : list)
            {
                m_data[count] = element;
                ++count;
            }
        }

        [[nodiscard]] static constexpr size_t size() noexcept { return N; }

        constexpr T& operator[](const size_t& index) noexcept { return m_data[index]; }
        constexpr const T& operator[](const size_t& index) const noexcept { return m_data[index]; }

        [[nodiscard]] constexpr const T& at(size_t index) const { return m_data[index]; }
        constexpr T& at(size_t index) { return m_data[index]; }

        [[nodiscard]] constexpr const T& front() const { return m_data[0]; }
        constexpr T& front() { return m_data[0]; }

        [[nodiscard]] constexpr const T& back() const { return m_data[N - 1]; }
        constexpr T& back() { return m_data[N]; }

        constexpr T* data() noexcept { return m_data; }
        [[nodiscard]] constexpr const T* data() const noexcept { return m_data; }

        static constexpr bool empty() noexcept { return N == 0; }

        [[nodiscard]] constexpr size_t max_size() const noexcept { return std::distance(begin(), end()); }

        void fill(const T& value) { std::fill(begin(), end(), value); }

        constexpr Iterator begin() { return Iterator(m_data); }
        constexpr Iterator end() { return Iterator(m_data + N); }

    private:
        T m_data[N];
    };
}
