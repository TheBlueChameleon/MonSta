#ifndef CLIHANDLER_HPP
#define CLIHANDLER_HPP

#include "cliinput.hpp"

CliInput parseCliInput(const int argc, const char* const argv[]);

void showModeHelp(const std::string &data);

#endif // CLIHANDLER_HPP
