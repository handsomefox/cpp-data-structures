#include "pch.h"

#include "Array.h"
#include "String.h"
#include "Vector.h"

int main()
{
	for (cpp::Array<int, 5> arr{ 1, 2, 3, 4, 5 }; const auto& element: arr)
	std::cout << element << ' ';

	for (const cpp::Vector vec{ 1, 2, 3, 4, 5, 6 }; const auto& element: vec)
	std::cout << element << ' ';

	const cpp::String str = "Hello world!";

	std::cout << '\n';
	for (const auto c : str)
		std::cout << c << ' ';
	return 0;
}
