find_package(GTest REQUIRED)

add_executable(tests_google tests_google.cpp)
target_link_libraries(tests_google derivative_lib GTest::gtest GTest::gtest_main)
add_test(NAME GoogleTests COMMAND tests_google)

find_package(Catch2 REQUIRED)

add_executable(tests_catch2 tests_catch2.cpp)
target_link_libraries(tests_catch2 derivative_lib Catch2::Catch2WithMain)
add_test(NAME Catch2Tests COMMAND tests_catch2)
