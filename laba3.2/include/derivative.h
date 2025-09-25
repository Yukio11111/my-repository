#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <functional>
#include <cmath>

namespace numeric {
    
    class DerivativeCalculator{
	public:
	    static double centralDifference(std::function<double(double)> f, double x, double h = 1e-5);

	    static double forwardDifference(std::function<double(double)> f, double x, double h = 1e-5);

	    static double backwardDifference(std::function<double(double)> f, double x, double h = 1e-5);

	    static double secondDerivative(std::function<double(double)> f, double x, double h = 1e-5);

    };

}

#endif