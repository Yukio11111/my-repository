cmake_minimum_required(VERSION 3.10)
project(lab2)

# Ищем Catch2 в системе
find_package(Catch2 REQUIRED)

add_library(iomanip INTERFACE)
target_include_directories(iomanip INTERFACE include)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/protect.cpp "#include <iomanip.hpp>\n")

file(GLOB TESTS tests/*.cpp)
add_executable(tests_iomanip ${TESTS} ${CMAKE_CURRENT_BINARY_DIR}/protect.cpp)
target_link_libraries(tests_iomanip iomanip Catch2::Catch2WithMain)
