#pragma once

#include <iostream>

#include "Array.h"
#include "String.h"
#include "Vector.h"

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
	std::cout << "String test:\n";

	const String str("Hello");
	String str2("Not Hello");

	std::cout << "str = " << str << '\n';
	std::cout << "Size of the str: " << str.size() << "\n";
	std::cout << "Length of the str: " << str.length() << "\n";

	std::cout << "str2 = " << str2 << '\n';
	std::cout << "Size of the str2: " << str2.size() << "\n";
	std::cout << "Length of the str2: " << str2.length() << "\n";

	std::cout << "Comparing str to str2: " << (str2 == str) << "\n";
	std::cout << "Comparing str to cstring: " << (str == "Hello") << "\n";

	std::cout << "Concatenated string: " << str2 + str << "\n";
	std::cout << "Concatenated string: " << str2 + " " + str << "\n";

	std::cout << "c_str() from str: " << str.c_str() << "\n";

	String str3("I like to code in C");
	std::cout << str3 << '\n';
	std::cout << "Length: " << str3.length() << '\n';
	std::cout << "Size: " << str3.size() << '\n';
	std::cout << "Empty: " << str3.empty() << '\n';

	const auto len = str3.length();

	str3.resize(len + 2, '+');
	std::cout << str3 << '\n';
	std::cout << "Length: " << str3.length() << '\n';
	std::cout << "Size: " << str3.size() << '\n';
	std::cout << "Capacity: " << str3.capacity() << '\n';
	std::cout << "Empty: " << str3.empty() << '\n';

	str3.resize(14);
	str3.resize(14);

	for (size_t i = 0; i < str3.length(); ++i)
	{
		std::cout << str3.at(i);
	}

	std::cout << '\n';
	std::cout << "Length: " << str3.length() << '\n';
	std::cout << "Size: " << str3.size() << '\n';
	std::cout << "Capacity: " << str3.capacity() << '\n';
	std::cout << "Empty: " << str3.empty() << '\n';

	str3.clear();
	str3.reserve(100);
	std::cout << str3 << '\n';
	std::cout << "Length: " << str3.length() << '\n';
	std::cout << "Size: " << str3.size() << '\n';
	std::cout << "Capacity: " << str3.capacity() << '\n';
	std::cout << "Empty: " << str3.empty() << '\n';

	str3.shrink_to_fit();
	std::cout << str3 << '\n';
	std::cout << "Length: " << str3.length() << '\n';
	std::cout << "Size: " << str3.size() << '\n';
	std::cout << "Capacity: " << str3.capacity() << '\n';
	std::cout << "Empty: " << str3.empty() << '\n';

	String str5("hello world.");
	str5.back() = '!';
	std::cout << str5 << '\n';
	str5.front() = 'H';
	std::cout << str5 << '\n';

	String str6;
	const String str7 = "Writing ";
	const String str8 = "print 10 and then 5 more";

	str6.append(str7);
	str6.append(str8, 6, 3);
	str6.append("dots are cool", 5);
	str6.append("here: ");
	str6.append(10u, '.');
	std::cout << str6 << '\n';

	String str9("There are two needles in this haystack with needles.");
	const String str10("needle");

	auto found = str9.find(str10);
	if (found != String::npos)
	{
		std::cout << "first 'needle' found at: " << found << '\n';
	}

	found = str9.find("needles are small", found + 1, 6);
	if (found != String::npos)
	{
		std::cout << "second 'needle' found at: " << found << '\n';
	}

	found = str9.find("haystack");
	if (found != String::npos)
	{
		std::cout << "'haystack' also found at: " << found << '\n';
	}

	found = str9.find('.');
	if (found != String::npos)
	{
		std::cout << "Period found at: " << found << '\n';
	}
	str9.replace(str9.find(str10), str10.length(), "stickys");
	std::cout << str9 << '\n';

	String str_iter;
	str_iter.resize(10);
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
