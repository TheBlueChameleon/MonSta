#ifndef BASEMODEDEFINITION_H
#define BASEMODEDEFINITION_H

#include "../operationmode.hpp"

#include "loggingdefinition.hpp"

struct BaseModeDefinition
{
    BaseModeDefinition(
        const OperationMode      mode,
        const LoggingDefinition& logging
    ) :
        mode(mode),
        logging(logging)
    {}
    virtual ~BaseModeDefinition() = default;

    const OperationMode     mode;
    const LoggingDefinition logging;
};

#endif // BASEMODEDEFINITION_H
