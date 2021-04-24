#include "Test/Test.hpp"
#include <iostream>

int main()
{
	mango::RunVectorTest();
	std::cin.get();
	system("CLS");
	mango::RunArrayTest();
	std::cin.get();
	system("CLS");
	mango::RunStringTest();
	std::cin.get();
}
