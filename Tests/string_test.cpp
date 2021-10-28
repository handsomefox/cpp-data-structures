#include "pch.h"

#include "../src/String.h"

namespace StringTests
{
	using namespace cpp;
	TEST(StringTest, CstrConstructor)
	{
		constexpr auto test = "Hello World!";
		const String str = test;

		EXPECT_STREQ(str.c_str(), test);
	}
	TEST(StringTest, StringConstructor)
	{
		const String str1 = "Hey!";
		const String str2 = str1;

		EXPECT_STREQ(str1.c_str(), str2.c_str());
	}
	TEST(StringTest, MoveConstructor)
	{
		const auto str(String("xd"));
		EXPECT_STREQ(str.c_str(), "xd");
	}

	TEST(StringTest, at)
	{
		const String str = "xx";
		const auto c = str.at(0);
		const auto c2 = str.at(1);
		EXPECT_EQ(c, c2);
	}
	TEST(StringTest, back)
	{
		const String str = "Hello";
		const auto c = str.back();
		const auto c2 = str.at(4);
		EXPECT_EQ(c, c2);
	}
	TEST(StringTest, front)
	{
		const String str = "Hello";
		const auto c = str.front();
		const auto c2 = str.at(0);
		EXPECT_EQ(c, c2);
	}
	TEST(StringTest, append)
	{
		String str = "He";
		String str2 = "llo";
		String str3 = str + str2;
		EXPECT_STREQ(str3.c_str(), "Hello");
	}
	TEST(StringTest, appendCstr)
	{
		String str = "He";
		String str3 = str + "llo";
		EXPECT_STREQ(str3.c_str(), "Hello");
	}
	TEST(StringTest, appendSubpos)
	{
		String str = "He";
		str.append(String("llo"), 0, 3);
		EXPECT_STREQ(str.c_str(), "Hello");
	}
	TEST(StringTest, appendCstrN)
	{
		String str = "He";
		str.append("llo", 3);
		EXPECT_STREQ(str.c_str(), "Hello");
	}
	TEST(StringTest, appendCharN)
	{
		String str = "He";
		str.append(3, 'c');
		EXPECT_STREQ(str.c_str(), "Heccc");
	}
	TEST(StringTest, empty)
	{
		String str;
		String str2 = "222";

		EXPECT_TRUE(str.empty());
		EXPECT_FALSE(str2.empty());
	}
	TEST(StringTest, clear)
	{
		String str = "222";
		str.clear();
		EXPECT_TRUE(str.empty());
	}
	TEST(StringTest, capacity)
	{
		String str;
		str.reserve(2);
		EXPECT_EQ(2, str.capacity());
	}
	TEST(StringTest, size)
	{
		String str = "1";
		EXPECT_EQ(2, str.size());
	}
	TEST(StringTest, length)
	{
		String str = "1";
		EXPECT_EQ(1, str.length());
	}
	TEST(StringTest, shrink_to_fit)
	{
		String str;
		str.reserve(100);
		EXPECT_EQ(str.capacity(), 100);

		str = "100";
		EXPECT_EQ(str.capacity(), 100);
		str.shrink_to_fit();
		EXPECT_EQ(str.capacity(), 4);
	}
}
