project(tests)

enable_testing()

add_executable(array_test array_test.cpp)
add_executable(string_test string_test.cpp)
add_executable(vector_test vector_test.cpp)

target_link_libraries(
        array_test
        gtest_main
)

target_link_libraries(
        string_test
        gtest_main
)

target_link_libraries(
        vector_test
        gtest_main
)

include(GoogleTest)

gtest_discover_tests(array_test)
gtest_discover_tests(string_test)
gtest_discover_tests(vector_test)
