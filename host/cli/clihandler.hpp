#ifndef CLIHANDLER_HPP
#define CLIHANDLER_HPP

#include <memory>

#include "../operationmodes/shared/basemodedefinition.hpp"

#include "cliinput.hpp"

CliInput readCliInput(const int argc, const char* const argv[]);

std::shared_ptr<const BaseModeDefinition> unpackCliInput(const CliInput& cliInput);

#endif // CLIHANDLER_HPP
