#include <iostream>
#include "numerical_derivatives.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Базовые численные производные", "[basic]") {
    double x = 2.0;
    double exact = TestFunctions::exact_deriv_square(x);
    
    SECTION("Производная вперед") {
        double result = NumericalDerivatives::forward_derivative(TestFunctions::square, x);
        REQUIRE(abs(result - exact) < 1e-4);
        cout << "✓ Производная вперед: " << result << " (ожидается: " << exact << ")" << endl;
    }
    
    SECTION("Производная назад") {
        double result = NumericalDerivatives::backward_derivative(TestFunctions::square, x);
        REQUIRE(abs(result - exact) < 1e-4);
        cout << "✓ Производная назад: " << result << " (ожидается: " << exact << ")" << endl;
    }
    
    SECTION("Центральная производная") {
        double result = NumericalDerivatives::central_derivative(TestFunctions::square, x);
        REQUIRE(abs(result - exact) < 1e-6);
        cout << "✓ Центральная производная: " << result << " (ожидается: " << exact << ")" << endl;
    }
}

TEST_CASE("Сравнение точности методов", "[accuracy]") {
    double x = 3.0;
    double exact = TestFunctions::exact_deriv_cube(x);
    
    double forward = NumericalDerivatives::forward_derivative(TestFunctions::cube, x);
    double backward = NumericalDerivatives::backward_derivative(TestFunctions::cube, x);
    double central = NumericalDerivatives::central_derivative(TestFunctions::cube, x);
    
    SECTION("Центральная производная точнее прямой") {
        REQUIRE(abs(central - exact) < abs(forward - exact));
        cout << "✓ Центральная производная точнее прямой" << endl;
    }
    
    SECTION("Центральная производная точнее обратной") {
        REQUIRE(abs(central - exact) < abs(backward - exact));
        cout << "✓ Центральная производная точнее обратной" << endl;
    }
    
    SECTION("Все методы дают близкие результаты") {
        REQUIRE(abs(forward - exact) < 1e-4);
        REQUIRE(abs(backward - exact) < 1e-4);
        REQUIRE(abs(central - exact) < 1e-6);
        cout << "✓ Все методы дают близкие результаты" << endl;
    }
}

TEST_CASE("Обработка ошибок и граничные случаи", "[errors]") {
    SECTION("Отрицательный шаг вызывает исключение") {
        REQUIRE_THROWS_AS(NumericalDerivatives::forward_derivative(TestFunctions::square, 2.0, -1e-5), runtime_error);
        cout << "✓ Отрицательный шаг вызывает исключение" << endl;
    }
    
    SECTION("Нулевой шаг вызывает исключение") {
        REQUIRE_THROWS_AS(NumericalDerivatives::backward_derivative(TestFunctions::square, 2.0, 0.0), runtime_error);
        cout << "✓ Нулевой шаг вызывает исключение" << endl;
    }
    
    SECTION("Производная синуса в особой точке") {
        double result = NumericalDerivatives::central_derivative(TestFunctions::sine_func, M_PI/2);
        REQUIRE(abs(result) < 1e-6);
        cout << "✓ Производная синуса в π/2: " << result << " (ожидается: 0)" << endl;
    }
}