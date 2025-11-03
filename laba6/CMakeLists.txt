# Устанавливаем минимально необходимую версию CMake.
cmake_minimum_required(VERSION 3.10)

# Определяем имя проекта и язык программирования.
project(ImageIteratorProject LANGUAGES CXX)

# Устанавливаем стандарт C++ (C++17 - хороший выбор).
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Поиск зависимостей ---

# ИЗМЕНЕНИЕ 1: Ищем Boost без указания компонентов,
# так как iterator - это header-only библиотека.
find_package(Boost REQUIRED)

# Ищем фреймворк для тестирования Catch2 (версии 3).
find_package(Catch2 REQUIRED)

# --- Настройка сборки тестов ---

# Создаём исполняемый файл для тестов из исходного кода.
add_executable(
    run_tests
    tests/iterator.cpp
)

# Указываем пути к заголовочным файлам, чтобы компилятор их нашёл.
target_include_directories(
    run_tests 
    PRIVATE
        # Путь к нашему `iterator.hpp`
        ${PROJECT_SOURCE_DIR}/include
        # Путь к заголовочным файлам Boost
        ${Boost_INCLUDE_DIRS}
)

# Привязываем (линкуем) необходимые библиотеки к нашему исполняемому файлу.
target_link_libraries(
    run_tests 
    PRIVATE
        # Catch2::Catch2WithMain предоставляет не только библиотеку,
        # но и готовую функцию main() для запуска тестов.
        Catch2::Catch2WithMain
        
        # ИЗМЕНЕНИЕ 2: Убрали линковку с Boost::iterator, так как она не нужна.
)

# --- Настройка для запуска тестов через CTest ---

# Включаем возможность тестирования в проекте.
enable_testing()

# Добавляем тест под именем "IteratorTests", который запускает наш исполняемый файл.
add_test(NAME IteratorTests COMMAND run_tests)