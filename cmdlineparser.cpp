#include "cmdlineparser.h"

using namespace std;

/**
 * @brief Parses the command-line arguments.
 * 
 * Loops through argv, checks if each argument matches a registered option.
 * If the option is a flag, it sets mutExclSelected_.
 * If the option requires a value, it parses the next argument as its value.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return true Always returns true (parsing succeeded).
 */
bool CmdLineParser::parseCmdLine(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {

        string arg = argv[i];

        if (options_.count(arg)) 
        {
            CmdLineOption *opt = options_[arg];

            // Flag option (no value required)
            CmdLineOptionFlag *flag = dynamic_cast<CmdLineOptionFlag*>(opt);
            if (flag) {
                mutExclSelected_ = flag;
                continue;
            }

            // Value option (needs next argument)
            if (i + 1 < argc) {
                opt->parseValue(argv[i + 1]);
                i++; // skip value after parsing
            }
        }
    }

    return true;
}
