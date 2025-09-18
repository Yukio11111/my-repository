cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

# Явно указываем что хотим только конфигурацию
if(NOT CMAKE_C_COMPILER)
    message(WARNING "No C compiler found - generating configuration only")
endif()

if(NOT CMAKE_CXX_COMPILER)
    message(WARNING "No C++ compiler found - generating configuration only")
endif()

add_executable(hello_world src/main.cpp src/util.cpp)
target_include_directories(hello_world PRIVATE include)