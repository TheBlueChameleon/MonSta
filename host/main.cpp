#include "cli/clihandler.hpp"

#include "operationmodes/entrypoint.hpp"
#include "operationmodes/shared/schemavalidation.hpp"

#include "errors.hpp"

void registerSchemas()
{
    OperationModes::registerSchemaSimulation();
    OperationModes::registerSchemaTemplate();
}

void run(const int argc, const char* const argv[])
{
    const CliInput cliInput = readCliInput(argc, argv);
    const std::shared_ptr<const BaseModeDefinition> runDefinition = unpackCliInput(cliInput);

    OperationModes::run(runDefinition);
}

#include <iostream>
#include <nlohmann/json.hpp>
#include "jsonservice/jsonschemabuilder.hpp"
void playground()
{
    using namespace JsonService;
    nlohmann::json data;
    JsonSchemaBuilder builder;

    data["null"] = {};
    data["also"] = nlohmann::json();
    data["object"] = nlohmann::json::parse("{}");
    data["dito"] = nlohmann::json::object();
    data["inner"] = {{"key", "value"}};

    builder.addProperty("prop")
    .setType(JsonType::INTEGER);
    builder.addProperty("directType", JsonType::STRING);
    builder.addProperty("noType");
    builder.addReference("ref", "desc");
    builder.setRequired({"foo", "bar"});
    builder.addSubSchema("subschema").addProperty("item").setArrayOfType(JsonType::STRING);


    std::cout << data.dump(2) << std::endl;
    std::cout << std::endl;
    std::cout << builder.build().dump(2) << std::endl;
}

int main(const int argc, const char* const argv[])
{
    // playground();
    // std::exit(0);

    try
    {
        registerSchemas();
        run(argc, argv);
    }
    catch (const CriticalAbort& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (const IllegalStateException& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "This means <the host dev> fucked up." << std::endl;
        std::cerr << "Please report to them what you were doing when this error occurred and give them a stern look." << std::endl;
        return -1;
    }
    catch (const ClientError& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "This means <the plugin dev> fucked up." << std::endl;
        std::cerr << "Please report to them what you were doing when this error occurred and give them a stern look." << std::endl;
        return -1;
    }

    return 0;
}
