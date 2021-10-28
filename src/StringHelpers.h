#pragma once
namespace cpp
{
	class StringHelpers
	{
	public:
		static size_t RequiredCapacity(const char* lhs, const char* rhs)
		{
			size_t l{ 0 }, r{ 0 };
			if (lhs != nullptr)
				l = strlen(lhs);
			if (rhs != nullptr)
				r = strlen(rhs);

			return l + r + 1;
		}
		static size_t RequiredCapacity(const char* string)
		{
			if (string != nullptr)
				return strlen(string) + 1;

			return 0;
		}
		static char* AllocTempBuf(const size_t size)
		{
			const auto temp = new char[size];
			return temp;
		}
		static void CopyStr(char* dst, const size_t buff_size, char const* src) { strcpy_s(dst, buff_size, src); }
		static void CatStr(char* dst, const size_t buff_size, char const* src) { strcat_s(dst, buff_size, src); }
		static void MoveStrToSelf(const char* dest, const char* src)
		{
			delete[] dest;
			dest = src;
		}
		static const char* SubStr(const char* string, const char* find) { return strstr(string, find); }
		static char* SubStr(char* string, const char* find) { return strstr(string, find); }
	};
}