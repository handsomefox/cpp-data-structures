#include "gtest/gtest.h"
#include "String.hpp"

TEST(StringTest, NormalConstructor)
{
	const String str = "Hello";
	const String str2 = "World";
	EXPECT_STRNE(str.c_str(), str2.c_str());
}

TEST(StringTest, size){
	const String str = "10";
	const String str2 = "1";
	EXPECT_NE(str.size(), str2.size());
}

TEST(StringTest, length){
	const String str = "10";
	const String str2 = "1";
	EXPECT_NE(str.length(), str2.length());
}

TEST(StringTest, capacity){
		const String str = "10";
		EXPECT_EQ(str.capacity(), 3);
}

TEST(StringTest, StringConstructor){
	const String str = "Hello";
	const String str2(str);
	EXPECT_EQ(str, str2);
}

TEST(StringTest, StringCompare){
	const String str = "Hello";
	const String str2 = "Hello";
	EXPECT_EQ(str, str2);
}

TEST(StringTest, CStringCompare){
	const String str = "Hello";
	const char *str2 = "Hello";

	bool res = str == str2;

	EXPECT_EQ(true, res);
}

TEST(StringTest, Concat){
	const String str = "Hello";	
	const char *str2 = "Hello";

	const char * res= "HelloHello";

	const String str3 = str + str2;
	bool isEqual = str3 == res;

	EXPECT_EQ(isEqual, true);
}

TEST(StringTest, ResizeTest){
		String str1("I like to code in C");
		String str2("I like to code in C++");

		const auto len = str1.length();
		str1.resize(len + 2, '+');
		EXPECT_EQ(str1, str2);
}

TEST(StringTest, AtTest){
	String str1 = "h";
	auto chr = str1.at(0);

	bool isEqual = str1[0] == chr;

	EXPECT_EQ(true, isEqual);
}

TEST(StringTest, Empty){
	String str1;
	EXPECT_EQ(true, str1.empty());
	str1 = "hello";
	EXPECT_NE(true, str1.empty());
}

TEST(StringTest, ShrinkToFit){
	String str1 = "123";
	str1.reserve(100);
	EXPECT_EQ(100, str1.capacity());

	str1.shrink_to_fit();

	EXPECT_EQ(4, str1.capacity());
}

TEST(StringTest, Back){
	String str1("hello world.");
	str1.back() = '!';
	EXPECT_EQ("hello world!", str1.c_str());
}

TEST(StringTest, Front){
	String str1("hello world.");
	str1.front() = 'H';
	EXPECT_EQ("Hello world.", str1.c_str());
}

TEST(StringTest, Append){
	String str6;
	const String str7 = "Writing ";
	const String str8 = "print 10 and then 5 more";
	str6.append(str7);
	str6.append(str8, 6, 3);
	str6.append("dots are cool", 5);
	str6.append("here: ");
	str6.append(10u, '.');
	EXPECT_EQ("Writing 10 dots here: .......... and then 5 more.....", str6.c_str());
}

TEST(StringTest, Find){
	String str9("There are two needles in this haystack with needles.");
	const String str10("needle");

	auto found = str9.find(str10);
	if (found != String::npos)
	{
		EXPECT_EQ(14, found);
	}

	found = str9.find("needles are small", found + 1, 6);
	if (found != String::npos)
	{
		EXPECT_EQ(44, found);
	}

	found = str9.find("haystack");
	if (found != String::npos)
	{
		EXPECT_EQ(30, found);
	}

	found = str9.find('.');
	if (found != String::npos)
	{
		EXPECT_EQ(51, found);
	}
}

TEST(StringTest, Replace){
  String base="this is a test string.";
  base.replace(0, 1, "c");
  EXPECT_EQ("chis is a test string.", base.c_str());
}
