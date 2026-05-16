#include <iostream>

#include <ClientApi.hpp>
#include <HostApi.hpp>

#include <runmodes/ITemplatesDefinition.hpp>

#include <templatesmode/templatesmode.hpp>

#include "util/dlxinitialization.hpp"
#include "serviceadapters/loggerserviceadapter.hpp"

#include "templatesmodetest.hpp"

#include "shared/schemavalidationconstants.hpp"

using namespace TemplateMode;

// ========================================================================== //
// Setup

void TemplatesModeTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
    static HostApi api = DlxInitialization::getServices();
    init(&api);
}

void TemplatesModeTest::TearDownTestSuite()
{}

// ========================================================================== //
// Tests

TEST_F(TemplatesModeTest, runFullTest)
{
    // ITemplatesDefinition input =
    // {
    //     true, true,     // writeSchemas, writeAllowedValues
    //     "",             // mechanicsDefinition
    //     "",             // player1Team
    //     "",             // player1Strategy
    //     "",             // player2Team
    //     "",             // player2Strategy
    //     "",             // pkmnDefs
    //     "",             // moveDefs
    //     "",             // typeDefs
    //     "",             // itemDefs
    //     ""              // args
    // };
    // ITemplatesDefinition output = run(input);
}
