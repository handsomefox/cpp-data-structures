#include "pch.h"

#include "Vector.hpp"

namespace VectorTests {
	using namespace cpp;
	TEST(vector_test, initializer_list)
	{
		Vector<int> vec{ 1,2 };

		EXPECT_EQ(vec[0], 1);
	}

	TEST(vector_test, copy_constructor)
	{
		const Vector<int> vec{ 3,4 };
		Vector<int> copied(vec);
		EXPECT_EQ(copied[0], 3);
	}

	TEST(vector_test, move_constructor)
	{
		const Vector<int> vec(Vector<int>{1, 2, 3});
		EXPECT_EQ(vec[0], 1);
	}

	TEST(vector_test, at)
	{
		const Vector<int> vec{ 1,2,3 };
		EXPECT_EQ(vec.at(0), 1);
	}

	TEST(vector_test, front)
	{
		const Vector<int> vec{ 1,2,3 };
		EXPECT_EQ(vec[0], vec.front());
	}

	TEST(vector_test, back)
	{
		const Vector<int> vec{ 1,2,3 };
		EXPECT_NE(vec[2], vec.back());
	}

	TEST(vector_test, iterators)
	{
		const Vector<int> vec{ 1,2,3 };

		constexpr int sum = 6;
		int sum2 = 0;

		for (const auto& elem : vec)
		{
			sum2 += elem;
		}
		EXPECT_EQ(sum, sum2);
	}

	TEST(vector_test, empty)
	{
		const Vector<int> vec;
		EXPECT_TRUE(vec.empty());
	}

	TEST(vector_test, size)
	{
		Vector<int> vec;
		vec.reserve(2);

		EXPECT_EQ(vec.capacity(), 2);
	}

	TEST(vector_test, reserve)
	{
		Vector<int> vec{ 1 };
		vec.reserve(2);

		EXPECT_EQ(vec.capacity(), 2);
		EXPECT_EQ(vec.at(0), 1);
	}

	TEST(vector_test, capacity)
	{
		Vector<int> vec;
		vec.reserve(2);
		EXPECT_EQ(vec.capacity(), 2);
	}

	TEST(vector_test, shrink_to_fit)
	{
		Vector<int> vec{ 1,2 };
		vec.reserve(10);
		vec.shrink_to_fit();
		EXPECT_EQ(vec.capacity(), 2);
		EXPECT_EQ(vec.at(1), 2);
	}

	TEST(vector_test, clear)
	{
		Vector<int> vec{ 1,2,3 };
		vec.clear();
		EXPECT_EQ(vec.size(), 0);
		EXPECT_EQ(vec.capacity(), 3);
		EXPECT_EQ(vec.at(0), 1);

		Vector<std::string> vec_string{ "123" };
		vec_string.clear();
		EXPECT_STREQ(vec_string.data()->c_str(), "");
	}

	TEST(vector_test, push_back)
	{
		Vector<int> vec;
		constexpr int two = 2;

		vec.push_back(two);
		EXPECT_EQ(vec.size(), 1);
		EXPECT_EQ(vec.at(0), 2);

		vec.push_back(two);
		EXPECT_EQ(vec.size(), 2);
		EXPECT_EQ(vec.at(1), two);
	}

	TEST(vector_test, push_back_temporary)
	{
		Vector<int> vec;
		vec.push_back(2);
		EXPECT_EQ(vec.at(0), 2);
	}

	TEST(vector_test, emplace_back)
	{
		Vector<int> vec;
		constexpr int two = 2;
		const int result = vec.emplace_back(two);
		EXPECT_EQ(two, vec.at(0));
		EXPECT_EQ(result, two);
	}

	TEST(vector_test, pop_back)
	{
		Vector<int> vec{ 1 };
		vec.pop_back();
		EXPECT_TRUE(vec.empty());
	}

	TEST(vector_test, resize)
	{
		Vector<int> vec;
		vec.resize(2);
		EXPECT_EQ(vec.capacity(), 2);
	}

	TEST(vector_test, resize_negative)
	{
		Vector<int> vec{ 1,2,3,4,5 };
		vec.resize(2);
		EXPECT_EQ(vec.capacity(), 2);
		EXPECT_EQ(vec.at(1), 2);
		EXPECT_ANY_THROW(vec.at(3));
	}

	TEST(vector_test, resize_with_value)
	{
		Vector<int> vec;
		vec.resize(2, 5);
		EXPECT_EQ(vec.capacity(), 2);
		EXPECT_EQ(vec.at(0), 5);
	}

	TEST(vector_test, swap)
	{
		Vector<int> vec1{ 1,2,3 };
		Vector<int> vec2{ 4,5,6 };
		vec1.swap(vec2);
		EXPECT_EQ(vec1.at(0), 4);
		EXPECT_EQ(vec2.at(0), 1);
	}

	TEST(vector_test, move_assignment)
	{
		Vector<int> vec = Vector<int>({ 1,2,3 });
		EXPECT_EQ(vec.at(0), 1);
	}

	TEST(vector_test, copy_assignment)
	{
		Vector<int> vec1{ 1,2,3 };
		Vector<int> vec2 = vec1;
		EXPECT_EQ(vec2.at(0), vec1.at(0));
	}
}
