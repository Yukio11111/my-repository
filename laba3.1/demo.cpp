#include <iostream>
#include <iomanip>
#include "numerical_derivatives.h"

using namespace std;

int main() {
    cout << "=== Демонстрация численных производных ===" << endl;
    cout << fixed << setprecision(6);
    
    // Тестирование разных функций
    double x = 2.0;
    cout << "\n1. Функция: f(x) = x²" << endl;
    cout << "Точка x = " << x << endl;
    cout << "Точная производная: " << TestFunctions::exact_deriv_square(x) << endl;
    cout << "Производная вперед: " << NumericalDerivatives::forward_derivative(TestFunctions::square, x) << endl;
    cout << "Производная назад: " << NumericalDerivatives::backward_derivative(TestFunctions::square, x) << endl;
    cout << "Центральная производная: " << NumericalDerivatives::central_derivative(TestFunctions::square, x) << endl;
    cout << "Вторая производная: " << NumericalDerivatives::second_derivative(TestFunctions::square, x) << endl;
    
    x = 1.0;
    cout << "\n2. Функция: f(x) = sin(x)" << endl;
    cout << "Точка x = " << x << endl;
    cout << "Точная производная: " << TestFunctions::exact_deriv_sine(x) << endl;
    cout << "Центральная производная: " << NumericalDerivatives::central_derivative(TestFunctions::sine_func, x) << endl;
    
    cout << "\n3. Функция: f(x) = exp(x)" << endl;
    cout << "Точка x = 0" << endl;
    cout << "Точная производная: " << TestFunctions::exact_deriv_exponential(0.0) << endl;
    cout << "Центральная производная: " << NumericalDerivatives::central_derivative(TestFunctions::exponential, 0.0) << endl;
    
    return 0;
}