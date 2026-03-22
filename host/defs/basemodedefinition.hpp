#ifndef BASEMODEDEFINITION_H
#define BASEMODEDEFINITION_H

#include "../cli/cliinput.hpp"

#include "../operationmode.hpp"

#include "loggingdefinition.hpp"

struct BaseModeDefinition
{
    BaseModeDefinition(
        const CliInput& cli,
        const LoggingDefinition& logging
    ) :
        mode(cli.mode),
        logging(logging),
        overwrite(cli.overwrite),
        createDirectories(cli.createDirectories),
        dryMode(cli.dryMode)
    {}
    virtual ~BaseModeDefinition() = default;

    const OperationMode     mode;
    const LoggingDefinition logging;
    const bool              overwrite;
    const bool              createDirectories;
    const bool              dryMode;
};

#endif // BASEMODEDEFINITION_H
