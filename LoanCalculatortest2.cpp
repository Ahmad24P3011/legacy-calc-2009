#include <iostream>
#include <cassert>
#include <cmath>
#include "LoanCalculator.h"

using namespace std;

void runTests() {
    cout << "Running Loan Calculator Tests..." << endl;
    cout << "=================================" << endl;
    
    // Test 1: Normal EMI Calculation
    cout << "Test 1: Normal EMI Calculation..." << endl;
    LoanCalculator loan(1000, 5, 1);
    double balance = loan.calculateBalance();
    cout << "Balance: " << balance << endl;
    assert(balance > 0);
    cout << "✓ PASSED" << endl << endl;
    
    // Test 2: Input Validation - Negative Principal
    cout << "Test 2: Input Validation (Negative Principal)..." << endl;
    try {
        LoanCalculator badLoan(-1000, 5, 1);
        cout << "✗ FAILED - Should have thrown exception" << endl;
    } catch (const exception& e) {
        cout << "✓ PASSED - Exception caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Test 3: Large Tenure
    cout << "Test 3: Large Tenure Calculation..." << endl;
    LoanCalculator largeLoan(1000000, 5, 50);
    double result = largeLoan.calculateBalance();
    cout << "Large loan result: " << result << endl;
    assert(result > 0);
    cout << "✓ PASSED" << endl << endl;
    
    cout << "=================================" << endl;
    cout << "All tests completed!" << endl;
}

int main() {
    runTests();
    return 0;
}