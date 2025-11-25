
#include <stdlib.h>
#include <exception>
#include <iostream>
#include "CmdLineHelper.h"
#include <stdexcept>
#include <string>
//#include <QApplication>
//#include <LoanCalcQtMainWindow.h>
#include "cmdlineparser.h"
#include "LoanCalculator.h"

using namespace std;

/**
 * @file main.cpp
 * @brief Entry point for Loan Calculator console application.
 *
 * This console version parses command-line arguments and performs
 * loan-related calculations such as EMI, loan balance, interest, and number of payments.
 */

int main(int argc, char **argv)
{
    LoanCalculator calculator; ///< The loan calculator object

    /**
     * @brief Check if any arguments are provided.
     *
     * If no command line arguments are given, the program prints a message and exits.
     */
    if(argc == 1)
    {
        cout << "No command line arguments provided. Exiting console version." << endl;
        return 0;
    }

    /**
     * @brief Parse the command line arguments
     *
     * Creates a CmdLineParser object and loads the options.
     * Then parses the command line to determine the calculation type.
     */
    CmdLineParser clp;
    loadCmdLine(clp);
    CALC_TYPE ct = parseCommandLine(argc, argv, clp, calculator);

    try
    {
        cout << endl;

        /**
         * @brief Perform calculation based on command-line argument type
         *
         * Depending on CALC_TYPE, calls the appropriate LoanCalculator function
         * and prints results to the console.
         */
        if(ct == CALC_BALANCE)
        {
            cout << "Loan Balance = " << (float) calculator.calculateLoanBalance() << endl;
        }
        else if(ct == CALC_PAYMENT)
        {
            float payment = calculator.calculatePayment();
            cout << "Monthly Payment    = " << payment << "\n"
                 << "Total amt paid     = " << (float) (payment*calculator.getPeriodTotal())
                 << endl;

            if(calculator.getOpeningPercent() != 0.0 || calculator.getOpeningFee() != 0.0)
            {
                cout << "Interest with fees = "
                     << (float) calculator.calculateEffectiveInterestRate()
                     << "%" << endl;
            }
        }
        else if(ct == CALC_NUMPAYMENTS)
        {
            cout << "Number of payments = " <<  calculator.calculateNumberPayments() << endl;
        }
        else if(ct == CALC_AMOUNT)
        {
            cout << "Initial Loan amount = " <<  calculator.calculateLoanAmount() << endl;
        }
        else if(ct == CALC_INTEREST)
        {
            cout << "Yearly Interest Rate = " <<  calculator.calculateInterestRate() << "%" << endl;
        }
        else if(ct == CALC_UNKNOWN)
        {
            // most likely the case that help was selected
            return 1;
        }
        else
        {
            cerr << "Unrecognized calculation type, exiting" << endl;
            return 0;
        }

        // Print the detailed state of the calculator
        cout << calculator.toString() << endl;
    }
    catch(const exception &e)
    {
        cerr << "Error executing loan calculator: " <<  e.what() << endl;
    }

    cout << endl;
}
