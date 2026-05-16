#include <iostream>

#include <HostApi.hpp>
#include <util/dlxinitialization.hpp>

#include "ClientApi.hpp"

#include "clientapitest.hpp"

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
// Test

TEST_F(ClientApiTest, InitTest_Success)
{
    init_engine_result = true;
    static HostApi api = getServices();
    ASSERT_TRUE(init(&api));
}

TEST_F(ClientApiTest, InitTest_FailNoApi)
{
    std::stringstream buffer;
    auto* old = std::cerr.rdbuf(buffer.rdbuf());

    ASSERT_FALSE(init(nullptr));
    EXPECT_EQ("No API information received!\n", buffer.str());

    std::cerr.rdbuf(old);
}

TEST_F(ClientApiTest, InitTest_FailInitEngine)
{
    init_engine_result = false;
    static HostApi api = getServices();
    ASSERT_FALSE(init(&api));
}
