#pragma once
#include "LoanCalculator.h"
#include "cmdlineparser.h"

enum CALC_TYPE { CALC_UNKNOWN=0, CALC_BALANCE=100, CALC_PAYMENT, CALC_NUMPAYMENTS, CALC_AMOUNT, CALC_INTEREST };

void loadCmdLine(CmdLineParser &clp);
CALC_TYPE parseCommandLine(int argc, char **argv, CmdLineParser &clp, LoanCalculator &calculator);
