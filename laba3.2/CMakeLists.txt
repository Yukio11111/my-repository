cmake_minimum_required(VERSION 3.14)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/googletest)
add_subdirectory(thirdparty/catch2)


add_library(derivative_lib include/derivative.cpp include/derivative.h)

target_include_directories(derivative_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(derivative src/main.cpp)
target_link_libraries(derivative derivative_lib)

enable_testing()
add_subdirectory(tests)