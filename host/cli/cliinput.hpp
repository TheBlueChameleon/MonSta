#ifndef CLIINPUT_H
#define CLIINPUT_H

#include <string>

#include "../operationmodes/operationmode.hpp"

struct CliInput
{
    static constexpr auto MODE               = "mode";
    static constexpr auto DATA               = "data";
    static constexpr auto OVERWRITE          = "overwrite";
    static constexpr auto CREATE_DIRECTORIES = "createDirectories";
    static constexpr auto DRY_MODE           = "dryMode";

    static constexpr auto SIMULATION   = "SIMULATION";
    static constexpr auto TEMPLATE     = "TEMPLATE";
    static constexpr auto SCHEMAEXPORT = "SCHEMAEXPORT";
    static constexpr auto REMOTE       = "REMOTE";
    static constexpr auto HELP         = "HELP";

    const OperationMode mode;
    const std::string   data;
    const bool          overwrite;
    const bool          createDirectories;
    const bool          dryMode;
};

#endif // CLIINPUT_H
