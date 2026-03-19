#ifndef CLIHANDLER_HPP
#define CLIHANDLER_HPP

#include "cliinput.hpp"

CliInput parseCliInput(const int argc, const char* const argv[]);

void handleCliInput(const CliInput& cliInput);

void showModeHelp(const std::string& data);

#endif // CLIHANDLER_HPP
