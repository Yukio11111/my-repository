#ifndef NUMERICAL_DERIVATIVES_H
#define NUMERICAL_DERIVATIVES_H

#include <cmath>
#include <stdexcept>

class NumericalDerivatives {
public:
    static double forward_derivative(double (*f)(double), double x, double h = 1e-5) {
        if (h <= 0) {
            throw std::runtime_error("Шаг должен быть положительным");
        }
        return (f(x + h) - f(x)) / h;
    }
    
    static double backward_derivative(double (*f)(double), double x, double h = 1e-5) {
        if (h <= 0) {
            throw std::runtime_error("Шаг должен быть положительным");
        }
        return (f(x) - f(x - h)) / h;
    }
    
    static double central_derivative(double (*f)(double), double x, double h = 1e-5) {
        if (h <= 0) {
            throw std::runtime_error("Шаг должен быть положительным");
        }
        return (f(x + h) - f(x - h)) / (2 * h);
    }
    
    static double second_derivative(double (*f)(double), double x, double h = 1e-5) {
        if (h <= 0) {
            throw std::runtime_error("Шаг должен быть положительным");
        }
        return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
    }
};

// Тестовые функции
namespace TestFunctions {
    inline double square(double x) { return x * x; }
    inline double cube(double x) { return x * x * x; }
    inline double sine_func(double x) { return std::sin(x); }
    inline double exponential(double x) { return std::exp(x); }
    
    // Точные производные
    inline double exact_deriv_square(double x) { return 2 * x; }
    inline double exact_deriv_cube(double x) { return 3 * x * x; }
    inline double exact_deriv_sine(double x) { return std::cos(x); }
    inline double exact_deriv_exponential(double x) { return std::exp(x); }
}

#endif