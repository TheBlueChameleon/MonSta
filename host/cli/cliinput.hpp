#ifndef CLIINPUT_H
#define CLIINPUT_H

#include <string>

struct CliInput
{
    enum class OperationMode
    {
        SIMULATION, TEMPLATE, REMOTE, HELP, INVALID
    };

    static constexpr auto MODE = "mode";
    static constexpr auto DATA = "data";

    static constexpr auto SIMULATION = "SIMULATION";
    static constexpr auto TEMPLATE   = "TEMPLATE";
    static constexpr auto REMOTE     = "REMOTE";
    static constexpr auto HELP       = "HELP";

    const OperationMode mode;
    const std::string   data;
};

#endif // CLIINPUT_H
