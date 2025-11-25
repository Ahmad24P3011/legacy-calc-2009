#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>

/**
 * @class LoanCalculator
 * @brief Performs loan-related calculations such as loan balance, payment amount, interest rate, and loan term.
 *
 * Supports initial payments, fees, and periodic calculations for monthly or total payments.
 */
class LoanCalculator
{
public:
    /**
     * @brief Default constructor. Initializes all members.
     */
    LoanCalculator();

    /**
     * @brief Destructor.
     */
    ~LoanCalculator() {}

    // ===== Setters & Getters =====
    /**
     * @brief Sets the total loan amount.
     * @param A Total loan amount.
     */
    inline void setAmount(double A) { amount_ = A; amountSet_ = true; }

    /**
     * @brief Gets the total loan amount.
     * @return Total loan amount.
     */
    inline double getAmount() const { return amount_; }

    /**
     * @brief Sets the initial down payment.
     * @param initialA Initial payment.
     */
    inline void setInitialPayment(double initialA) { initialPayment_ = initialA; }

    /**
     * @brief Gets the initial down payment.
     * @return Initial payment.
     */
    inline double getInitialPayment() const { return initialPayment_; }

    /**
     * @brief Sets the annual interest rate (percentage).
     * @param i Annual interest rate (e.g., 6.75 for 6.75%).
     */
    void setInterest(double i) { interest_ = i; interestPeriodic_ = i / 100.0 / 12.0; interestSet_ = true; }

    /**
     * @brief Gets the annual interest rate.
     * @return Annual interest rate.
     */
    inline double getInterest() const { return interest_; }

    /**
     * @brief Gets the monthly periodic interest rate.
     * @return Monthly interest rate.
     */
    inline double getPeriodicInterest() const { return interestPeriodic_; }

    /**
     * @brief Sets the monthly payment amount.
     * @param P Monthly payment.
     */
    void setPayment(double P) { payment_ = P; paymentSet_ = true; }

    /**
     * @brief Gets the monthly payment amount.
     * @return Monthly payment.
     */
    inline double getPayment() const { return payment_; }

    /**
     * @brief Sets the total number of payment periods.
     * @param N Total number of periods.
     */
    void setPeriodTotal(int N) { periodTotal_ = N; periodTotalSet_ = true; }

    /**
     * @brief Gets the total number of payment periods.
     * @return Total periods.
     */
    inline int getPeriodTotal() const { return periodTotal_; }

    /**
     * @brief Sets the number of elapsed periods.
     * @param n Number of periods elapsed.
     */
    void setPeriodElapsed(int n) { periodElapsed_ = n; periodElapsedSet_ = true; }

    /**
     * @brief Gets the number of elapsed periods.
     * @return Number of periods elapsed.
     */
    inline int getPeriodElapsed() const { return periodElapsed_; }

    /**
     * @brief Sets a fixed opening fee for the loan.
     * @param fee Opening fee.
     */
    inline void setOpeningFee(double fee) { openingFee_ = fee; }

    /**
     * @brief Gets the opening fee.
     * @return Opening fee.
     */
    inline double getOpeningFee() const { return openingFee_; }

    /**
     * @brief Sets a percentage opening fee for the loan.
     * @param percent Opening fee percentage.
     */
    inline void setOpeningPercent(double percent) { openingPercent_ = percent; }

    /**
     * @brief Gets the opening fee percentage.
     * @return Opening fee percentage.
     */
    inline double getOpeningPercent() const { return openingPercent_; }

    /**
     * @brief Resets all loan values and flags.
     */
    inline void reset() {
        amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0.0;
        periodTotal_ = periodElapsed_ = 0;
        amountSet_ = interestSet_ = paymentSet_ = periodTotalSet_ = periodElapsedSet_ = false;
    }

    // ===== Calculation Methods =====
    /**
     * @brief Calculates the remaining loan balance after elapsed periods.
     * @return Remaining loan balance.
     */
    double calculateLoanBalance();

    /**
     * @brief Calculates the required monthly payment.
     * @return Monthly payment amount.
     */
    double calculatePayment();

    /**
     * @brief Calculates the total number of payments required for the loan.
     * @return Number of payments.
     */
    double calculateNumberPayments();

    /**
     * @brief Calculates the original loan amount based on payments and interest.
     * @return Loan amount.
     */
    double calculateLoanAmount();

    /**
     * @brief Estimates the annual interest rate based on loan parameters.
     * @return Annual interest rate as a percentage.
     */
    double calculateInterestRate();

    /**
     * @brief Calculates the effective interest rate including fees.
     * @return Effective interest rate as a percentage.
     */
    double calculateEffectiveInterestRate();

    /**
     * @brief Returns a string summary of the loan parameters.
     * @return Formatted string with loan details.
     */
    std::string toString();

private:
    double amount_;          ///< Total loan amount
    bool amountSet_;

    double initialPayment_;  ///< Initial payment

    double interest_;        ///< Annual interest rate
    double interestPeriodic_;///< Monthly interest rate
    bool interestSet_;

    double payment_;         ///< Monthly payment
    bool paymentSet_;

    int periodTotal_;        ///< Total payment periods
    bool periodTotalSet_;

    int periodElapsed_;      ///< Elapsed payment periods
    bool periodElapsedSet_;

    double openingFee_;      ///< Fixed opening fee
    double openingPercent_;  ///< Opening fee percentage
};

#endif // LOANCALCULATOR_H_INCLUDED

