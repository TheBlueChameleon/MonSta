#ifndef SIMULATIONINPUTS_H
#define SIMULATIONINPUTS_H

#include <MatchDefinitions.hpp>

#include "environmentdefinition.hpp"

struct SimulationInputs
{
    EnvironmentDefinition envDef;
    MatchDefinition       matchDef;
};

#endif // SIMULATIONINPUTS_H
