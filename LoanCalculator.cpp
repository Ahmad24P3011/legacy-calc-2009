#include "LoanCalculator.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace std;

LoanCalculator::LoanCalculator() :
    amountSet_(false),
    initialPayment_(0.0),
    interestSet_(false),
    paymentSet_(false),
    periodTotalSet_(false),
    periodElapsedSet_(false),
    openingFee_(0.0),
    openingPercent_(0.0),
    interestPeriodic_(0.0)
{
}

/**
 * @brief Calculates the remaining loan balance.
 * @return Remaining loan balance.
 * @throws std::invalid_argument if required parameters are not set.
 */
double LoanCalculator::calculateLoanBalance()
{
    if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
        throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation");

    return (amount_ * pow(1.0 + interestPeriodic_, static_cast<double>(periodElapsed_))) -
           (payment_ / interestPeriodic_) *
           (pow(1.0 + interestPeriodic_, static_cast<double>(periodElapsed_)) - 1.0);
}

/**
 * @brief Calculates the monthly payment required.
 * @return Monthly payment amount.
 */
double LoanCalculator::calculatePayment()
{
    if(!amountSet_ || !interestSet_ || !periodTotalSet_)
        throw invalid_argument("Must set loan amount, interest, and total period for this calculation");

    double totalAmount = amount_ - initialPayment_;
    totalAmount += openingFee_ + totalAmount * (openingPercent_ / 100.0);

    if(totalAmount <= 0.0)
        throw invalid_argument("Loan amount minus initial payment must be positive");

    return (interestPeriodic_ * totalAmount) /
           (1.0 - pow(1.0 + interestPeriodic_, -1.0 * static_cast<double>(periodTotal_)));
}

/**
 * @brief Calculates the total number of payments required.
 * @return Number of payments.
 */
double LoanCalculator::calculateNumberPayments()
{
    if(!amountSet_ || !interestSet_ || !paymentSet_)
        throw invalid_argument("Must set loan amount, interest, and payment for this calculation");

    return (-1.0 * log10(1.0 - (interestPeriodic_ * amount_ / payment_))) /
           log10(1.0 + interestPeriodic_);
}

/**
 * @brief Calculates the original loan amount.
 * @return Loan amount.
 */
double LoanCalculator::calculateLoanAmount()
{
    if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
        throw invalid_argument("Must set payment, interest, and total period for this calculation");

    return (payment_ / interestPeriodic_) *
           (1.0 - pow(1.0 + interestPeriodic_, -1.0 * static_cast<double>(periodTotal_)));
}

/**
 * @brief Estimates the annual interest rate.
 * @return Annual interest rate as a percentage.
 */
double LoanCalculator::calculateInterestRate()
{
    if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
        throw invalid_argument("Must set amount, payment, and total period for this calculation");

    double q = log10(1.0 + 1.0 / periodTotal_) / log10(2.0);
    double monthlyInterest = pow(pow(1.0 + payment_ / amount_, 1.0 / q) - 1.0, q) - 1.0;

    return monthlyInterest * 12.0 * 100.0;
}

/**
 * @brief Calculates effective interest rate including fees.
 * @return Effective annual interest rate.
 */
double LoanCalculator::calculateEffectiveInterestRate()
{
    if(!amountSet_ || !periodTotalSet_)
        throw invalid_argument("Must set amount and total period for this calculation");

    double payment = calculatePayment();
    double totalAmount = amount_ - initialPayment_;
    double q = log10(1.0 + 1.0 / periodTotal_) / log10(2.0);
    double monthlyInterest = pow(pow(1.0 + payment / totalAmount, 1.0 / q) - 1.0, q) - 1.0;

    return monthlyInterest * 12.0 * 100.0;
}

/**
 * @brief Returns a formatted string of the current loan settings.
 * @return Loan information string.
 */
std::string LoanCalculator::toString()
{
    stringstream ss;

    if(amountSet_)
        ss << "Initial Amount:      " << amount_ << "\n";

    if(initialPayment_ != 0.0)
    {
        ss << "Initial Payment:     " << initialPayment_ << "\n";
        ss << "Actual Loan Amount:  " << (amount_ - initialPayment_) << "\n";
    }

    if(interestSet_)
        ss << "Yearly Interest:     " << interest_ << "%\n";

    if(paymentSet_)
        ss << "Monthly payment:     " << payment_ << "\n";

    if(periodTotalSet_)
        ss << "Loan Period:         " << periodTotal_ << " months\n";

    if(periodElapsedSet_)
        ss << "Elapsed Period:      " << periodElapsed_ << " months\n";

    if(openingFee_ != 0.0)
        ss << "Opening Fee:       " << openingFee_ << "\n";

    if(openingPercent_ != 0.0)
        ss << "Opening Fee %:       " << openingPercent_ << "% = "
           << (openingPercent_ / 100.0) * (amount_ - initialPayment_) << "\n";

    return ss.str();
}
