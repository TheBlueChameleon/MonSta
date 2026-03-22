#ifndef SIMULATIONMODEDEFINITION_H
#define SIMULATIONMODEDEFINITION_H

#include <MatchDefinitions.hpp>

#include "basemodedefinition.hpp"
#include "simulatordefinition.hpp"

struct SimulationModeDefinition : public BaseModeDefinition
{
    SimulationModeDefinition(
        const CliInput& cli,
        const LoggingDefinition& logging,
        const SimulatorDefinition& simulator,
        const MatchDefinition& match
    ):
        BaseModeDefinition(cli, logging),
        simulator(simulator),
        match(match)
    {}

    const SimulatorDefinition simulator;
    const MatchDefinition     match;
};

#endif // SIMULATIONMODEDEFINITION_H
