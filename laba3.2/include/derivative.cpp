#include "derivative.h"

namespace numeric {

    double DerivativeCalculator::centralDifference(std::function<double(double)> f, double x, double h){
	
	return (f(x + h) - f(x - h)) / (2 * h);
    }


    double DerivativeCalculator::forwardDifference(std::function<double(double)> f, double x, double h){
	
	return (f(x + h) -f(x)) / h;
    }


    double DerivativeCalculator::backwardDifference(std::function<double(double)> f, double x, double h){
	
	return (f(x) - f(x - h)) / h;
    }


    double DerivativeCalculator::secondDerivative(std::function<double(double)> f, double x, double h){
	
	return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
    }
}