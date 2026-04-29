#ifndef SIMULATIONMODEDEFINITION_HPP
#define SIMULATIONMODEDEFINITION_HPP

#include "operationmodes/shared/basemodedefinition.hpp"

#include "defs/matchdefinition.hpp"
#include "defs/simulatordefinition.hpp"

namespace OperationModes
{
    struct SimulationModeDefinition : public BaseModeDefinition
    {
        SimulationModeDefinition(
            const CliInput& cli,
            const LoggingDefinition& logging,
            const PathsDefinition& paths,
            const SimulatorDefinition& simulator,
            const MatchDefinition& match
        ):
            BaseModeDefinition(cli, logging, paths),
            simulator(simulator),
            match(match)
        {}

        const SimulatorDefinition simulator;
        const MatchDefinition     match;
    };
}

#endif // SIMULATIONMODEDEFINITION_HPP
