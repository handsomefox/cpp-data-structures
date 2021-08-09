cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(cpp-data-structures)

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

set(gtest_disable_pthreads ON)
add_subdirectory(lib/googletest)
