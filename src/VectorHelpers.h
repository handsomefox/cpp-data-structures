#pragma once

#include <type_traits>

namespace cpp
{
	template <typename T>
	class VectorHelpers
	{
	public:
		static void Move(T* dest, T* src, const size_t count)
		{
			if constexpr (std::is_trivial_v<T>)
				memmove_s(dest, count * sizeof(T), src, count * sizeof(T));

			for (size_t i = 0; i < count; ++i)
			{
				if (dest <= src)
					new (&dest[i]) T(std::move(src[i]));
				else
					new (&dest[count - i - 1]) T(std::move(src[count - i - 1]));
			}
		}
		static void Copy(T* dest, const T* src, const size_t count)
		{
			if constexpr (std::is_trivial_v<T>)
				memcpy_s(dest, count * sizeof(T), src, count * sizeof(T));

			for (size_t i = 0; i < count; ++i)
			{
				if (dest <= src)
					new (&dest[i]) T(src[i]);
				else
					new (&dest[count - i - 1]) T(src[count - i - 1]);
			}
		}
		constexpr static T* Alloc(const size_t size)
		{
			auto mem = new T[size * sizeof(T)];
			return mem;
		}
		constexpr static void Dealloc(const T* p) { delete[] p; }
		constexpr static void Destroy(const T& p) { p.~T(); }
		constexpr static T Construct() { return T{ }; }
		constexpr static T Construct(const T& value) { return T{ value }; }
	};
}