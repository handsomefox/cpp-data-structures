#include "../src/Array.h"
#include "gtest/gtest.h"

namespace ArrayTests
{
	using namespace cpp;
	TEST(array_test, initializer_list)
	{
		Array<int, 2> arr{ 1, 2 };
		EXPECT_EQ(arr[0], 1);
	}

	TEST(array_test, copy_constructor)
	{
		const Array<int, 2> arr{ 3, 4 };
		Array<int, 2> copied(arr);
		EXPECT_EQ(copied[0], 3);
	}

	TEST(array_test, move_constructor)
	{
		const auto arr(Array<int, 3>{ 1, 2, 3 });
		EXPECT_EQ(arr[0], 1);
	}

	TEST(array_test, at)
	{
		const Array<int, 3> arr{ 1, 2, 3 };
		EXPECT_EQ(arr.at(0), 1);
	}

	TEST(array_test, front)
	{
		const Array<int, 3> arr{ 1, 2, 3 };
		EXPECT_EQ(arr[0], arr.front());
	}

	TEST(array_test, back)
	{
		const Array<int, 3> arr{ 1, 2, 3 };
		EXPECT_EQ(arr[2], arr.back());
	}

	TEST(array_test, iterators)
	{
		Array<int, 3> arr{ 1, 2, 3 };
		constexpr int sum = 6;
		int sum2 = 0;
		for (const auto elem : arr)
			sum2 += elem;

		EXPECT_EQ(sum, sum2);
	}

	TEST(array_test, empty)
	{
		Array<int, 1> arr{};
		EXPECT_FALSE(arr.empty());
	}

	TEST(array_test, size)
	{
		Array<int, 2> arr{};
		EXPECT_EQ(arr.size(), 2);
	}

	TEST(array_test, fill)
	{
		Array<int, 3> arr{};
		arr.fill(50);
		EXPECT_EQ(arr[0], 50);
	}

	TEST(array_test, move_assignment)
	{
		auto arr = Array<int, 3>({ 1, 2, 3 });
		EXPECT_EQ(arr.at(0), 1);
	}

	TEST(array_test, copy_assignment)
	{
		Array<int, 3> arr1{ 1, 2, 3 };
		Array<int, 3> arr2 = arr1;
		EXPECT_EQ(arr2.at(0), arr1.at(0));
	}
}// namespace ArrayTests
