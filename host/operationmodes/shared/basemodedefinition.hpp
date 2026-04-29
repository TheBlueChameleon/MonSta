#ifndef BASEMODEDEFINITION_HPP
#define BASEMODEDEFINITION_HPP

#include "cli/cliinput.hpp"

#include "operationmodes/operationmode.hpp"

#include "defs/loggingdefinition.hpp"
#include "defs/pathsdefinition.hpp"

namespace OperationModes
{
    struct BaseModeDefinition
    {
        BaseModeDefinition(
            const CliInput& cli,
            const LoggingDefinition& logging,
            const PathsDefinition& paths
        ) :
            mode(cli.mode),
            logging(logging),
            paths(paths),
            overwrite(cli.overwrite),
            createDirectories(cli.createDirectories),
            dryMode(cli.dryMode)
        {}
        virtual ~BaseModeDefinition() = default;

        const OperationMode     mode;
        const LoggingDefinition logging;
        const PathsDefinition   paths;
        const bool              overwrite;
        const bool              createDirectories;
        const bool              dryMode;
    };
}

#endif // BASEMODEDEFINITION_HPP
