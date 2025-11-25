#include "gtest/gtest.h"
#include "LoanCalculator.h"
#include <stdexcept>

//  Normal EMI calculation
TEST(LoanCalculatorTest, NormalEMI) {
    LoanCalculator loan(1000, 5, 1);  // principal = 1000, rate = 5%, tenure = 1 year
    EXPECT_DOUBLE_EQ(loan.calculateBalance(), 1050);  // expected balance = 1050
}

//  Invalid input handling
TEST(LoanCalculatorTest, InvalidInput) {
    // Negative principal should throw exception
    EXPECT_THROW(LoanCalculator loan(-1000, 5, 1), std::invalid_argument);
    
    // Negative interest rate
    EXPECT_THROW(LoanCalculator loan(1000, -5, 1), std::invalid_argument);
    
    // Negative tenure
    EXPECT_THROW(LoanCalculator loan(1000, 5, -1), std::invalid_argument);
}

//  Large tenure calculations without overflow
TEST(LoanCalculatorTest, LargeTenure) {
    LoanCalculator loan(1000000, 5, 50); // very large principal and tenure
    double result = loan.calculateBalance();
    EXPECT_GT(result, 0);  // check result is positive and no overflow
}

// Main function for running all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
