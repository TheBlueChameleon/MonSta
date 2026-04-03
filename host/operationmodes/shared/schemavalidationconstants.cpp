#include <string>
using namespace std::string_literals;

#include "jsonservice/jsonschemabuilder.hpp"
#include "jsonservice/jsonservice.hpp"
using namespace JsonService;

#include "schemavalidationconstants.hpp"

using Json = nlohmann::json;

namespace OperationModes
{
    // ====================================================================== //
    // SHARED

    // ---------------------------------------------------------------------- //
    // logging

    static const JsonSubSchemaBuilder makeLoggingSubSchema()
    {
        auto logging = JsonSubSchemaBuilder(JKEY_LOGGING);

        logging.addProperty(JKEY_LOGGING_LOGFILE, JsonType::STRING);

        logging.addProperty(JKEY_LOGGING_LOGLEVEL, JsonType::INTEGER)
        .setMinimum(0)
        .setMaximum(6)
        .setDefault(2);

        return logging;
    }

    // ====================================================================== //
    // SIMULATION

    // ---------------------------------------------------------------------- //
    // simulator

    static const JsonSubSchemaBuilder makeSimulatorSubSchema()
    {
        auto simulator = JsonSubSchemaBuilder(JKEY_SIMULATOR)
                         .setRequired(
        {
            JKEY_SIMULATOR_ENGINE, JKEY_SIMULATOR_INPUTDIRECTORY, JKEY_SIMULATOR_OUTPUTDIRECTORY
        });

        simulator.addProperty(JKEY_SIMULATOR_ENGINE, JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_INPUTDIRECTORY, JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_OUTPUTDIRECTORY, JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_REPETITIONS, JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(100);

        simulator.addProperty(JKEY_SIMULATOR_MAXTURNS, JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(100);

        simulator.addProperty(JKEY_SIMULATOR_THREADCOUNT, JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(1);

        simulator.addProperty(JKEY_SIMULATOR_ARGS, JsonType::STRING);

        return simulator;
    }

    // ---------------------------------------------------------------------- //
    // match definition

    static const JsonSubSchemaBuilder makeMatchDefinitionSubSchema()
    {
        auto matchDefinition = JsonSubSchemaBuilder(JKEY_MATCHDEFINITION)
                               .setRequired(
        {
            JKEY_MATCHDEFINITION_PLAYER1TEAM,
            JKEY_MATCHDEFINITION_PLAYER1STRATETY,
            JKEY_MATCHDEFINITION_PLAYER2TEAM,
            JKEY_MATCHDEFINITION_PLAYER2STRATETY,
            JKEY_MATCHDEFINITION_PKMNDEFS,
            JKEY_MATCHDEFINITION_MOVEDEFS,
            JKEY_MATCHDEFINITION_TYPEDEFS,
            JKEY_MATCHDEFINITION_ITEMDEFS
        });

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1STRATETY, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2STRATETY, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1TEAM, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2TEAM, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PKMNDEFS, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_MOVEDEFS, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_TYPEDEFS, JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_ITEMDEFS, JsonType::STRING);

        return matchDefinition;
    }

    // ---------------------------------------------------------------------- //
    // FULL SCHEMA

    static const JsonSchemaBuilder makeSimulationSchema()
    {
        auto simulation = JsonSchemaBuilder()
                          .addReference(JKEY_LOGGING, makeLoggingSubSchema())
                          .addReference(JKEY_SIMULATOR, makeSimulatorSubSchema())
                          .addReference(JKEY_MATCHDEFINITION, makeMatchDefinitionSubSchema())
                          .setRequired(
        {
            JKEY_SIMULATOR, JKEY_MATCHDEFINITION
        });

        return simulation;
    }

    void registerSchemaSimulation()
    {
        JsonService::add(
            JTAG_SIMULATION,
            std::move(makeSimulationSchema().build())
        );
    }

    // ====================================================================== //
    // TEMPLATE

    // ---------------------------------------------------------------------- //
    // template

    static const JsonSubSchemaBuilder makeTemplateDefinitionSubSchema()
    {
        auto result = JsonSubSchemaBuilder(JKEY_TEMPLATES)
                      .setRequired(
        {
            JKEY_TEMPLATES_ENGINE, JKEY_TEMPLATES_OUTPUTDIRECTORY
        });

        result.addProperty(JKEY_TEMPLATES_ENGINE, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_OUTPUTDIRECTORY, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_WRITESCHEMAS, JsonType::BOOLEAN)
        .setDefault(true);

        result.addProperty(JKEY_TEMPLATES_PLAYER1TEAM, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER1STRATEGY, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER2TEAM, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER2STRATEGY, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PKMNDEFS, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_MOVEDEFS, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_TYPEDEFS, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_ITEMDEFS, JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_ARGS, JsonType::STRING);

        return result;
    }

    // ---------------------------------------------------------------------- //
    // FULL SCHEMA

    static const JsonSchemaBuilder makeTemplateSchema()
    {
        auto result = JsonSchemaBuilder()
                      .addReference(JKEY_LOGGING, makeLoggingSubSchema())
                      .addReference(JKEY_TEMPLATES, makeTemplateDefinitionSubSchema())
                      .setRequired(
        {
            JKEY_TEMPLATES
        });

        return result;
    }

    void registerSchemaTemplate()
    {
        JsonService::add(
            JTAG_TEMPLATES,
            std::move(makeTemplateSchema().build())
        );
    }
}
