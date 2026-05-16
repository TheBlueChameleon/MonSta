#ifndef TEMPLATESMODETEST_HPP
#define TEMPLATESMODETEST_HPP

#include <string>

#include <gtest/gtest.h>

class TemplatesModeTest : public testing::Test
{
    protected:
        static std::string mechanicsDefinition;
        static constexpr auto PATH = "../engines/libEngine-Gen1.so";

        TemplatesModeTest() = default;

        static void SetUpTestSuite();
        static void TearDownTestSuite();
};

#endif // TEMPLATESMODETEST_HPP
