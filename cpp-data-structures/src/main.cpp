#include "pch.h"

#include "Array.hpp"

int main()
{
    cpp::Array<int, 4> arr{ 1, 2, 3, 4 };

    for (const auto& elem : arr)
    {
        std::cout << elem << '\n';
    }


    std::cout << "Hello world!\n";
    return 0;
}
