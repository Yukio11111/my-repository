#include <iostream>
#include "simple_gtest.h"
#include "numerical_derivatives.h"

using namespace std;

// Тест 1: Базовая функциональность
TEST(NumericalDerivatives, BasicFunctionality) {
    cout << "=== Тест 1: Базовая функциональность ===" << endl;
    
    double x = 2.0;
    double exact = TestFunctions::exact_deriv_square(x);
    
    double forward = NumericalDerivatives::forward_derivative(TestFunctions::square, x);
    double backward = NumericalDerivatives::backward_derivative(TestFunctions::square, x);
    double central = NumericalDerivatives::central_derivative(TestFunctions::square, x);
    
    EXPECT_NEAR(forward, exact, 1e-4);
    EXPECT_NEAR(backward, exact, 1e-4);
    EXPECT_NEAR(central, exact, 1e-6);
}

// Тест 2: Тригонометрические функции  
TEST(NumericalDerivatives, TrigonometricFunctions) {
    cout << "=== Тест 2: Тригонометрические функции ===" << endl;
    
    double x = 1.0;
    double exact = TestFunctions::exact_deriv_sine(x);
    
    double result = NumericalDerivatives::central_derivative(TestFunctions::sine_func, x);
    EXPECT_NEAR(result, exact, 1e-6);
    
    result = NumericalDerivatives::central_derivative(TestFunctions::exponential, 0.0);
    EXPECT_NEAR(result, 1.0, 1e-6);
}

// Тест 3: Обработка ошибок
TEST(NumericalDerivatives, ErrorHandlingAndEdgeCases) {
    cout << "=== Тест 3: Обработка ошибок ===" << endl;
    
    EXPECT_THROW(NumericalDerivatives::forward_derivative(TestFunctions::square, 2.0, -0.1), runtime_error);
    EXPECT_THROW(NumericalDerivatives::backward_derivative(TestFunctions::square, 2.0, 0.0), runtime_error);
    
    double result = NumericalDerivatives::central_derivative(TestFunctions::exponential, 10.0);
    EXPECT_GT(result, 0);
    
    result = NumericalDerivatives::central_derivative(TestFunctions::square, -3.0);
    EXPECT_NEAR(result, -6.0, 1e-6);
}

// Регистрация тестов
REGISTER_TEST(NumericalDerivatives_BasicFunctionality_Test);
REGISTER_TEST(NumericalDerivatives_TrigonometricFunctions_Test);
REGISTER_TEST(NumericalDerivatives_ErrorHandlingAndEdgeCases_Test);

RUN_ALL_TESTS();