#include <functional>
#include <iostream>

#include <HostApi.hpp>
#include <util/dlxinitialization.hpp>

#include "ClientApi.hpp"

#include "clientapitest.hpp"

using namespace DlxInitialization;

// ========================================================================== //
// Stubs

HOST_API_EXPORT
{
    void HOST_API_CALL hangUp() {}

    ITemplatesDefinition HOST_API_CALL startTemplatesMode(const ITemplatesDefinition templatesDefinition)
    {
        return templatesDefinition;
    }

    void HOST_API_CALL setupSimulationMode(const IMatchDefinition matchDefinition) {}
}

static bool init_engine_result = true;
bool init_engine()
{
    return init_engine_result;
}

// ========================================================================== //
// Tools

std::string runWithCapturedStdErr(std::function<void()> codeUnderTest)
{
    std::stringstream buffer;
    auto* old = std::cerr.rdbuf(buffer.rdbuf());

    codeUnderTest();

    std::cerr.rdbuf(old);
    return buffer.str();
}

// ========================================================================== //
// Test

TEST_F(ClientApiTest, InitTest_Success)
{
    init_engine_result = true;
    HostApi api = getServices();
    ASSERT_TRUE(init(&api));
}

TEST_F(ClientApiTest, InitTest_Fail_NoApi)
{
    const std::string log = runWithCapturedStdErr([]
    {
        ASSERT_FALSE(init(nullptr));
    });
    EXPECT_EQ("No API information received!\n", log);
}

TEST_F(ClientApiTest, InitTest_Fail_NoLoggerService)
{
    init_engine_result = true;
    auto api = HostApi {};

    const std::string log = runWithCapturedStdErr([&api]
    {
        ASSERT_FALSE(init(&api));
    });
    EXPECT_EQ("ErrorService was not initialized!\n", log);
}

TEST_F(ClientApiTest, InitTest_Fail_InitEngine)
{
    init_engine_result = false;
    static HostApi api = getServices();
    ASSERT_FALSE(init(&api));
}
