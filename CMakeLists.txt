# CMakeList.txt : CMake project for cpp-data-structures, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

project ("cpp-data-structures")

SET(sources ${sources} 
    "main.cpp"
    "Array.h"
    "Iterator.h"
    "String.h"
    "Vector.h"
    "Test.h"
)
# Add source to this project's executable.
add_executable (cpp-data-structures ${sources})

# TODO: Add tests and install targets if needed.
