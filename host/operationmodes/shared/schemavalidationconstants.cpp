#include <string>
using namespace std::string_literals;

#include <services/ILoggerService.hpp>

#include "jsonservice/jsonschemabuilder.hpp"
#include "jsonservice/jsonservice.hpp"
using namespace JsonService;

#include "schemavalidationconstants.hpp"

namespace OperationModes
{
    // ====================================================================== //
    // TAGS

    const IJsonServiceTypes::JsonTag JTAG_BASE       = IJsonServiceTypes::JsonTag(":storage:/host/");
    const IJsonServiceTypes::JsonTag JTAG_SIMULATION = IJsonServiceTypes::JsonTag(":storage:/host/:validation:/simulation.json");
    const IJsonServiceTypes::JsonTag JTAG_TEMPLATES  = IJsonServiceTypes::JsonTag(":storage:/host/:validation:/templates.json");

    // ====================================================================== //
    // SHARED

    // ---------------------------------------------------------------------- //
    // logging

    static const JsonSchemaBuilder makeLoggingSubSchema()
    {
        auto logging = JsonSchemaBuilder(JKEY_LOGGING);

        logging.addProperty(JKEY_LOGGING_LOGFILE, IJsonServiceTypes::JsonType::STRING);

        logging.addProperty(JKEY_LOGGING_LOGLEVEL, IJsonServiceTypes::JsonType::STRING)
        .setEnum(
        {
            ILoggerService::LOGLEVELNAME_TRACE,
            ILoggerService::LOGLEVELNAME_DEBUG,
            ILoggerService::LOGLEVELNAME_INFO,
            ILoggerService::LOGLEVELNAME_WARNING,
            ILoggerService::LOGLEVELNAME_ERROR,
            ILoggerService::LOGLEVELNAME_CRITICAL,
            ILoggerService::LOGLEVELNAME_OFF
        })
        .setDefault(ILoggerService::LOGLEVELNAME_INFO);

        return logging;
    }

    // ====================================================================== //
    // SIMULATION

    // ---------------------------------------------------------------------- //
    // simulator

    static const JsonSchemaBuilder makeSimulatorSubSchema()
    {
        auto simulator = JsonSchemaBuilder(JKEY_SIMULATOR)
                         .setRequired(
        {
            JKEY_SIMULATOR_ENGINE, JKEY_SIMULATOR_INPUTDIRECTORY, JKEY_SIMULATOR_OUTPUTDIRECTORY
        });

        simulator.addProperty(JKEY_SIMULATOR_ENGINE, IJsonServiceTypes::JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_INPUTDIRECTORY, IJsonServiceTypes::JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_OUTPUTDIRECTORY, IJsonServiceTypes::JsonType::STRING);

        simulator.addProperty(JKEY_SIMULATOR_REPETITIONS, IJsonServiceTypes::JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(100);

        simulator.addProperty(JKEY_SIMULATOR_MAXTURNS, IJsonServiceTypes::JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(100);

        simulator.addProperty(JKEY_SIMULATOR_THREADCOUNT, IJsonServiceTypes::JsonType::INTEGER)
        .setMinimum(1)
        .setDefault(1);

        simulator.addProperty(JKEY_SIMULATOR_ARGS, IJsonServiceTypes::JsonType::STRING);

        return simulator;
    }

    // ---------------------------------------------------------------------- //
    // match definition

    static const JsonSchemaBuilder makeMatchDefinitionSubSchema()
    {
        auto matchDefinition = JsonSchemaBuilder(JKEY_MATCHDEFINITION)
                               .setRequired(
        {
            JKEY_MATCHDEFINITION_MECHANICS,
            JKEY_MATCHDEFINITION_PLAYER1TEAM,
            JKEY_MATCHDEFINITION_PLAYER1STRATETY,
            JKEY_MATCHDEFINITION_PLAYER2TEAM,
            JKEY_MATCHDEFINITION_PLAYER2STRATETY,
            JKEY_MATCHDEFINITION_PKMNDEFS,
            JKEY_MATCHDEFINITION_MOVEDEFS,
            JKEY_MATCHDEFINITION_TYPEDEFS,
            JKEY_MATCHDEFINITION_ITEMDEFS
        });

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_MECHANICS, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1STRATETY, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2STRATETY, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER1TEAM, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PLAYER2TEAM, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_PKMNDEFS, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_MOVEDEFS, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_TYPEDEFS, IJsonServiceTypes::JsonType::STRING);

        matchDefinition.addProperty(JKEY_MATCHDEFINITION_ITEMDEFS, IJsonServiceTypes::JsonType::STRING);

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

    static const JsonSchemaBuilder makeTemplateDefinitionSubSchema()
    {
        auto result = JsonSchemaBuilder(JKEY_TEMPLATES)
                      .setRequired(
        {
            JKEY_TEMPLATES_ENGINE, JKEY_TEMPLATES_OUTPUTDIRECTORY
        });

        result.addProperty(JKEY_TEMPLATES_ENGINE, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_OUTPUTDIRECTORY, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_WRITESCHEMAS, IJsonServiceTypes::JsonType::BOOLEAN)
        .setDefault(true);

        result.addProperty(JKEY_TEMPLATES_PLAYER1TEAM, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER1STRATEGY, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER2TEAM, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PLAYER2STRATEGY, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_PKMNDEFS, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_MOVEDEFS, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_TYPEDEFS, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_ITEMDEFS, IJsonServiceTypes::JsonType::STRING);

        result.addProperty(JKEY_TEMPLATES_ARGS, IJsonServiceTypes::JsonType::STRING);

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
