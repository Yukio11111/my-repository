cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Создаем STATIC библиотеку из util файлов
add_library(util_lib STATIC src/util.cpp)

# Указываем где искать заголовки для библиотеки
target_include_directories(util_lib PUBLIC include)

# Создаем исполняемый файл
add_executable(hello_world src/main.cpp)

# Связываем библиотеку с исполняемым файлом
target_link_libraries(hello_world PRIVATE util_lib)