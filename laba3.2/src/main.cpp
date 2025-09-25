#include <iostream>
#include <cmath>
#include "derivative.h"

int main() {
    auto square = [](double x) { return x * x; };
    
    double x = 2.0;
    
    std::cout << "Функция: f(x) = x^2" << std::endl;
    std::cout << "Точное значение производной в x=" << x << ": " << 2*x << std::endl;
    std::cout << "Центральная разность: " << numeric::DerivativeCalculator::centralDifference(square, x) << std::endl;
    std::cout << "Правая разность: " << numeric::DerivativeCalculator::forwardDifference(square, x) << std::endl;
    std::cout << "Левая разность: " << numeric::DerivativeCalculator::backwardDifference(square, x) << std::endl;
    std::cout << "Вторая производная: " << numeric::DerivativeCalculator::secondDerivative(square, x) << std::endl;
    
    return 0;
}