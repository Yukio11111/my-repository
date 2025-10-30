# Устанавливаем минимальную требуемую версию CMake и название проекта
cmake_minimum_required(VERSION 3.14)
project(proxy_lab CXX)

# Включаем стандарт C++17 для современных возможностей языка
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Автоматическая загрузка Catch2 ---
# Подключаем модуль FetchContent для управления зависимостями
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.6.0
)
# Делаем Catch2 доступным в проекте
FetchContent_MakeAvailable(Catch2)
# --- Конец блока загрузки Catch2 ---

# Находим стандартную библиотеку для работы с потоками
find_package(Threads REQUIRED)

# Добавляем "виртуальную" библиотеку для нашего кода
# Это нужно, чтобы указать, где лежат заголовочные файлы
add_library(proxy INTERFACE)
target_include_directories(proxy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(proxy INTERFACE Threads::Threads)

# Находим все файлы с тестами в папке tests/
file(GLOB TESTS tests/*.cpp)

# Создаем исполняемый файл для тестов
add_executable(tests_proxy ${TESTS})

# Подключаем (линкуем) к нашим тестам:
# 1. Наш код (proxy)
# 2. Библиотеку Catch2 с функцией main
target_link_libraries(tests_proxy
    PRIVATE
    proxy
    Catch2::Catch2WithMain
)

# Включаем интеграцию с системой тестирования CTest
include(Catch)
catch_discover_tests(tests_proxy)