#include <gtest/gtest.h>
#include <cmath>
#include "derivative.h"


TEST(DerivativeTest, LinearFunction) {
    auto linear = [](double x) { return 3*x + 2; };
    double x = 5.0;
    
    
    EXPECT_NEAR(numeric::DerivativeCalculator::centralDifference(linear, x), 3.0, 1e-9);
    EXPECT_NEAR(numeric::DerivativeCalculator::forwardDifference(linear, x), 3.0, 1e-9);
    EXPECT_NEAR(numeric::DerivativeCalculator::backwardDifference(linear, x), 3.0, 1e-9);
    EXPECT_NEAR(numeric::DerivativeCalculator::secondDerivative(linear, x), 0.0, 1e-9);
}


TEST(DerivativeTest, QuadraticFunction) {
    auto square = [](double x) { return x*x; };
    double x = 3.0;
    
    
    EXPECT_NEAR(numeric::DerivativeCalculator::centralDifference(square, x), 6.0, 1e-4);
    EXPECT_NEAR(numeric::DerivativeCalculator::forwardDifference(square, x), 6.0, 1e-4);
    EXPECT_NEAR(numeric::DerivativeCalculator::backwardDifference(square, x), 6.0, 1e-4);
    EXPECT_NEAR(numeric::DerivativeCalculator::secondDerivative(square, x), 2.0, 1e-4);
}


TEST(DerivativeTest, TrigonometricFunction) {
    auto sin_func = [](double x) { return std::sin(x); };
    double x = M_PI/4; // 45 градусов
    
   
    EXPECT_NEAR(numeric::DerivativeCalculator::centralDifference(sin_func, x), std::cos(x), 1e-4);
    EXPECT_NEAR(numeric::DerivativeCalculator::secondDerivative(sin_func, x), -std::sin(x), 1e-4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}