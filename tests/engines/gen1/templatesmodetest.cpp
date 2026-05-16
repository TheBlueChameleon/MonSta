#include <iostream>
#include <format>

#include <fileservice/fileservice.hpp>

#include <runmodes/ITemplatesDefinition.hpp>

#include <templatesmode/templatesmode.hpp>

#include "util/dlxinitialization.hpp"
#include "serviceadapters/loggerserviceadapter.hpp"
#include "serviceadapters/fileserviceadapter.hpp"

#include "shared/schemavalidationconstants.hpp"

#include "templatesmodetest.hpp"

using namespace TemplateMode;

// ========================================================================== //
// Setup

void TemplatesModeTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
    FileService::setOutputBasePath(IFileService::DEBUGSTREAM);
    DlxInitialization::initServices();
}

void TemplatesModeTest::TearDownTestSuite()
{}

// ========================================================================== //
// Tools

std::string TemplatesModeTest::mechanicsDefinition = std::format("{}/mechDef.json", IFileService::DEBUGSTREAM);

// ========================================================================== //
// Tests

TEST_F(TemplatesModeTest, runFullTestWithDefaults)
{
    ITemplatesDefinition input =
    {
        true, true,     // writeSchemas, writeAllowedValues
        "",             // mechanicsDefinition
        "",             // player1Team
        "",             // player1Strategy
        "",             // player2Team
        "",             // player2Strategy
        "",             // pkmnDefs
        "",             // moveDefs
        "",             // typeDefs
        "",             // itemDefs
        ""              // args
    };
    ITemplatesDefinition output = run(input);

    EXPECT_STREQ(output.mechanicsDefinition,    TemplateMode::MECHANICS_DEFINITION_FILE);
    EXPECT_STREQ(output.player1Team,            TemplateMode::PLAYER1_TEAMDEFINITION_FILE);
    EXPECT_STREQ(output.player1Strategy,        TemplateMode::PLAYER1_STRATEGY_FILE);
    EXPECT_STREQ(output.player2Team,            TemplateMode::PLAYER2_TEAMDEFINITION_FILE);
    EXPECT_STREQ(output.player2Strategy,        TemplateMode::PLAYER2_STRATEGY_FILE);
    EXPECT_STREQ(output.pkmnDefs,               TemplateMode::PKMN_DEFINITION_FILE);
    EXPECT_STREQ(output.moveDefs,               TemplateMode::MOVE_DEFINITION_FILE);
    EXPECT_STREQ(output.typeDefs,               TemplateMode::TYPE_DEFINITION_FILE);
    EXPECT_STREQ(output.itemDefs,               TemplateMode::ITEM_DEFINITION_FILE);
    EXPECT_STREQ(output.args,                   input.args);

    std::string mechDefContent = FileServiceAdapter::getDebugStreamContent(SchemaValidation::filename_mechanicsDefinitionSchema);
    EXPECT_TRUE(mechDefContent.ends_with('\0'));

    std::string teamDefContent = FileServiceAdapter::getDebugStreamContent(SchemaValidation::filename_teamDefinitionSchema);
    EXPECT_TRUE(teamDefContent.ends_with('\0'));
}

