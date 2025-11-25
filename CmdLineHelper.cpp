#include "CmdLineHelper.h"
#include <iostream>
#include <string>
#include <cstdlib> // for atof, atoi

using namespace std;

// Load the available command line options (optional help text)
void loadCmdLine(CmdLineParser &clp) {
    // For simplicity, we won’t use help text in this console version
    clp.setMainHelpText("Loan Calculator Options");
}

// Parse command line arguments and update the calculator
CALC_TYPE parseCommandLine(int argc, char **argv, CmdLineParser &clp, LoanCalculator &calculator) {
    CALC_TYPE calcType = CALC_UNKNOWN;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--amount" && i + 1 < argc) {
            calculator.setAmount(atof(argv[++i]));
        } 
        else if (arg == "--initialPayment" && i + 1 < argc) {
            calculator.setInitialPayment(atof(argv[++i]));
        } 
        else if (arg == "--interest" && i + 1 < argc) {
            calculator.setInterest(atof(argv[++i]));
        } 
        else if (arg == "--payment" && i + 1 < argc) {
            calculator.setPayment(atof(argv[++i]));
        } 
        else if (arg == "--periodTotal" && i + 1 < argc) {
            calculator.setPeriodTotal(atoi(argv[++i]));
        } 
        else if (arg == "--periodElapsed" && i + 1 < argc) {
            calculator.setPeriodElapsed(atoi(argv[++i]));
        } 
        else if (arg == "--openingFee" && i + 1 < argc) {
            calculator.setOpeningFee(atof(argv[++i]));
        } 
        else if (arg == "--openingPercent" && i + 1 < argc) {
            calculator.setOpeningPercent(atof(argv[++i]));
        } 
        else if (arg == "--balance") {
            calcType = CALC_BALANCE;
        } 
        else if (arg == "--paymentAmt") {
            calcType = CALC_PAYMENT;
        } 
        else if (arg == "--numPayments") {
            calcType = CALC_NUMPAYMENTS;
        } 
        else if (arg == "--loanAmount") {
            calcType = CALC_AMOUNT;
        } 
        else if (arg == "--interestRate") {
            calcType = CALC_INTEREST;
        } 
        else if (arg == "--help") {
            calcType = CALC_UNKNOWN;
        } 
        else {
            cerr << "Unknown argument: " << arg << endl;
        }
    }

    return calcType;
}
