#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Abstract base class representing a command-line option.
 */
class CmdLineOption {
public:
    virtual ~CmdLineOption() {}
    
    /**
     * @brief Parses the value of the command-line option.
     * @param value The string value from the command line.
     * @return true if parsing succeeded, false otherwise.
     */
    virtual bool parseValue(const string &value) = 0;
};

/**
 * @brief Integer command-line option.
 */
class CmdLineOptionInt : public CmdLineOption {
    int value_;
public:
    /**
     * @brief Constructor.
     * @param help Help text for this option.
     */
    CmdLineOptionInt(const string &help) : value_(0) {}

    bool parseValue(const string &value) override {
        value_ = stoi(value);
        return true;
    }

    /**
     * @brief Returns the stored integer value.
     * @return Integer value of this option.
     */
    int getValue() const { return value_; }
};

/**
 * @brief Float command-line option.
 */
class CmdLineOptionFloat : public CmdLineOption {
    float value_;
public:
    /**
     * @brief Constructor.
     * @param help Help text for this option.
     */
    CmdLineOptionFloat(const string &help) : value_(0) {}

    bool parseValue(const string &value) override {
        value_ = stof(value);
        return true;
    }

    /**
     * @brief Returns the stored float value.
     * @return Float value of this option.
     */
    float getValue() const { return value_; }
};

/**
 * @brief Flag command-line option (boolean, no value required).
 */
class CmdLineOptionFlag : public CmdLineOption {
    string name_;
    int key_;
public:
    /**
     * @brief Constructor.
     * @param name Flag name.
     * @param help Help text.
     * @param defaultVal Default value (ignored here).
     * @param key Unique key to identify the flag.
     */
    CmdLineOptionFlag(const string &name, const string &help, bool defaultVal, int key)
        : name_(name), key_(key) {}

    bool parseValue(const string &value) override {
        return true; ///< Flags don’t need values
    }

    /**
     * @brief Returns the key of this flag.
     */
    int getValueKey() const { return key_; }

    /**
     * @brief Returns the name of this flag.
     */
    string getName() const { return name_; }
};

/**
 * @brief Command-line parser class.
 */
class CmdLineParser {
    map<string, CmdLineOption*> options_; ///< All registered options
    CmdLineOptionFlag* mutExclSelected_;  ///< Currently selected mutually exclusive flag

public:
    /**
     * @brief Constructor.
     */
    CmdLineParser() : mutExclSelected_(nullptr) {}

    /**
     * @brief Adds a normal command-line option.
     * @param flag Option flag (e.g., "-amount").
     * @param opt Pointer to the CmdLineOption object.
     */
    void addCmdLineOption(const string &flag, CmdLineOption *opt) {
        options_[flag] = opt;
    }

    /**
     * @brief Adds a mutually exclusive flag option.
     * @param flag Option flag.
     * @param opt Pointer to the CmdLineOptionFlag object.
     */
    void addMutExclCmdLineOption(const string &flag, CmdLineOptionFlag *opt) {
        options_[flag] = opt;
    }

    /**
     * @brief Sets main help text displayed at the beginning.
     * @param txt Help text string.
     */
    void setMainHelpText(const string &txt) {}

    /**
     * @brief Sets main help text displayed at the end.
     * @param txt Help text string.
     */
    void setMainHelpTextEnd(const string &txt) {}

    /**
     * @brief Sets mutually exclusive usage text.
     * @param txt Usage text string.
     */
    void setMutExclUsageText(const string &txt) {}

    /**
     * @brief Sets minimum number of arguments required.
     * @param n Minimum number of args.
     */
    void setMinNumberArgs(int n) {}

    /**
     * @brief Parses the command-line arguments.
     * @param argc Argument count.
     * @param argv Argument vector.
     * @return true if parsing succeeded, false otherwise.
     */
    bool parseCmdLine(int argc, char **argv);

    /**
     * @brief Returns a pointer to the command-line option for a given key.
     * @param key Option flag.
     * @return Pointer to CmdLineOption if found, nullptr otherwise.
     */
    CmdLineOption* getCmdLineOption(const string &key) {
        if (options_.count(key)) return options_[key];
        return nullptr;
    }

    /**
     * @brief Returns the currently selected mutually exclusive flag.
     * @return Pointer to CmdLineOptionFlag.
     */
    CmdLineOptionFlag* getMutExclOption() {
        return mutExclSelected_;
    }

    /**
     * @brief Prints the usage text.
     */
    void printUsage() {
        cout << "Usage: loanCalc [options]\n";
    }
};
