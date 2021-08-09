#pragma once

#include "../src/Array.hpp"
#include "../src/String.hpp"
#include "../src/Vector.hpp"

#include <iostream>

inline void RunArrayTest()
{
	std::cout << "Array test:\n";
	Array<int, 2> array{};
	std::cout << "array.empty() " << array.empty() << "\n";
	for (size_t i = 0; i < array.size(); ++i)
	{
		std::cout << "Array element " << i << " = " << array[i] << "\n";
	}
	array[0] = 2;
	array[1] = 2;
	std::cout << "All array elements are set to 2\n";
	for (size_t i = 0; i < array.size(); ++i)
	{
		std::cout << "Array element " << i << " = " << array[i] << "\n";
	}

	std::cout << "Iterator test\n";
	Array<int, 10> arr_iterator{};
	std::fill(arr_iterator.begin(), arr_iterator.end(), -2);

	for (const auto& number : arr_iterator)
	{
		std::cout << "Number = " << number << "\n";
	}
}

inline void RunStringTest()
{

}

inline void RunVectorTest()
{
	std::cout << "Vector test:\n";
	Vector<int> vec;
	vec.print();
	std::cout << "Empty: " << vec.empty() << "\n";
	vec.reserve(100);
	std::cout << "Adding data to Vector\n";
	vec.push_back(1);
	vec.push_back(2);
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

	Vector<int> vec3;
	vec3[0] = 2;
	auto vec4 = vec3;
	std::cout << "vec3[0]: " << vec3[0] << "\n";
	std::cout << "vec4[0]: " << vec4[0] << "\n";

	std::cout << "Iterator test\n";
	Vector<int> vec_iterator;
	vec_iterator.resize(10);
	std::fill(vec_iterator.begin(), vec_iterator.end(), -1);

	for (const auto& number : vec_iterator)
	{
		std::cout << "Number = " << number << "\n";
	}
}
