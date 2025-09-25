#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <cmath>
#include "derivative.h"

using Catch::Approx;

TEST_CASE("Linear function derivatives", "[linear]") {
    auto linear = [](double x) { return 4*x - 1; };
    double x = 2.0;
    
    REQUIRE(numeric::DerivativeCalculator::centralDifference(linear, x) == Approx(4.0).margin(1e-6));
    REQUIRE(numeric::DerivativeCalculator::forwardDifference(linear, x) == Approx(4.0).margin(1e-6));
    REQUIRE(numeric::DerivativeCalculator::secondDerivative(linear, x) == Approx(0.0).margin(1e-4));
}

TEST_CASE("Exponential function derivatives", "[exponential]") {
    auto exp_func = [](double x) { return std::exp(x); };
    double x = 1.0;
    
    REQUIRE(numeric::DerivativeCalculator::centralDifference(exp_func, x) == Approx(std::exp(x)).margin(1e-6));
    REQUIRE(numeric::DerivativeCalculator::secondDerivative(exp_func, x) == Approx(std::exp(x)).margin(1e-4));
}

TEST_CASE("Different step sizes", "[step]") {
    auto cube = [](double x) { return x*x*x; };
    double x = 2.0;
    
    SECTION("Large step") {
        REQUIRE(numeric::DerivativeCalculator::centralDifference(cube, x, 0.1) == Approx(12.0).margin(0.1));
    }
    
    SECTION("Small step") {
        REQUIRE(numeric::DerivativeCalculator::centralDifference(cube, x, 1e-6) == Approx(12.0).margin(1e-4));
    }
}