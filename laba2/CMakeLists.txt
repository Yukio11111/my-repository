cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исходные файлы
add_executable(hello_world 
    src/main.cpp 
    src/util.cpp
)

# Включаем директорию с заголовками
target_include_directories(hello_world PRIVATE include)