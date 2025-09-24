#include <iostream>
#include <cmath>
#include <stdexcept>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

// Базовые функции для тестирования
double square(double x) {
    return x * x;
}

double cube(double x) {
    return x * x * x;
}

double sine_func(double x) {
    return sin(x);
}

double exponential(double x) {
    return exp(x);
}

// Точные производные для тестирования
double exact_deriv_square(double x) {
    return 2 * x;
}

double exact_deriv_cube(double x) {
    return 3 * x * x;
}

double exact_deriv_sine(double x) {
    return cos(x);
}

double exact_deriv_exponential(double x) {
    return exp(x);
}

// Реализация численных производных
double forward_derivative(double (*f)(double), double x, double h = 1e-5) {
    if (h <= 0) {
        throw runtime_error("Шаг должен быть положительным");
    }
    return (f(x + h) - f(x)) / h;
}

double backward_derivative(double (*f)(double), double x, double h = 1e-5) {
    if (h <= 0) {
        throw runtime_error("Шаг должен быть положительным");
    }
    return (f(x) - f(x - h)) / h;
}

double central_derivative(double (*f)(double), double x, double h = 1e-5) {
    if (h <= 0) {
        throw runtime_error("Шаг должен быть положительным");
    }
    return (f(x + h) - f(x - h)) / (2 * h);
}

double second_derivative(double (*f)(double), double x, double h = 1e-5) {
    if (h <= 0) {
        throw runtime_error("Шаг должен быть положительным");
    }
    return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

// Тесты с использованием Catch2
TEST_CASE("Численные производные для квадратичной функции", "[derivatives][square]") {
    double x = 2.0;
    double exact = exact_deriv_square(x);
    
    SECTION("Производная вперед") {
        double result = forward_derivative(square, x);
        REQUIRE(abs(result - exact) < 1e-4);
    }
    
    SECTION("Производная назад") {
        double result = backward_derivative(square, x);
        REQUIRE(abs(result - exact) < 1e-4);
    }
    
    SECTION("Центральная производная") {
        double result = central_derivative(square, x);
        REQUIRE(abs(result - exact) < 1e-6);
    }
    
    SECTION("Вторая производная") {
        double result = second_derivative(square, x);
        REQUIRE(abs(result - 2.0) < 1e-4);
    }
}

TEST_CASE("Численные производные для кубической функции", "[derivatives][cube]") {
    double x = 3.0;
    double exact = exact_deriv_cube(x);
    
    SECTION("Сравнение точности методов") {
        double forward = forward_derivative(cube, x);
        double backward = backward_derivative(cube, x);
        double central = central_derivative(cube, x);
        
        REQUIRE(abs(central - exact) < abs(forward - exact));
        REQUIRE(abs(central - exact) < abs(backward - exact));
    }
    
    SECTION("Разные значения шага") {
        double h1 = 1e-3;
        double h2 = 1e-6;
        
        double result1 = central_derivative(cube, x, h1);
        double result2 = central_derivative(cube, x, h2);
        
        REQUIRE(abs(result1 - exact) < 1e-4);
        REQUIRE(abs(result2 - exact) < 1e-4);
    }
}

TEST_CASE("Численные производные для тригонометрических функций", "[derivatives][trig]") {
    double x = 1.0;
    double exact = exact_deriv_sine(x);
    
    SECTION("Производная синуса") {
        double result = central_derivative(sine_func, x);
        REQUIRE(abs(result - exact) < 1e-6);
    }
    
    SECTION("Производная в особых точках") {
        double result = central_derivative(sine_func, M_PI/2);
        REQUIRE(abs(result) < 1e-6);
    }
}

TEST_CASE("Численные производные для экспоненциальной функции", "[derivatives][exp]") {
    double x = 1.0;
    double exact = exact_deriv_exponential(x);
    
    SECTION("Производная экспоненты") {
        double result = central_derivative(exponential, x);
        REQUIRE(abs(result - exact) < 1e-6);
    }
    
    SECTION("Производная в нуле") {
        double result = central_derivative(exponential, 0.0);
        REQUIRE(abs(result - 1.0) < 1e-6);
    }
}

TEST_CASE("Обработка ошибок в численных производных", "[derivatives][errors]") {
    SECTION("Отрицательный шаг") {
        REQUIRE_THROWS_AS(forward_derivative(square, 2.0, -1e-5), runtime_error);
    }
    
    SECTION("Нулевой шаг") {
        REQUIRE_THROWS_AS(backward_derivative(square, 2.0, 0.0), runtime_error);
    }
    
    SECTION("Очень маленький шаг") {
        REQUIRE_NOTHROW(central_derivative(square, 2.0, 1e-15));
    }
}

TEST_CASE("Граничные случаи", "[derivatives][boundary]") {
    SECTION("Большой шаг") {
        double result = central_derivative(square, 2.0, 0.1);
        REQUIRE(abs(result - 4.0) < 0.1);
    }
    
    SECTION("Очень большие значения") {
        double result = central_derivative(exponential, 10.0);
        REQUIRE(result > 0);
    }
    
    SECTION("Отрицательные значения") {
        double result = central_derivative(square, -3.0);
        REQUIRE(abs(result - (-6.0)) < 1e-6);
    }
}