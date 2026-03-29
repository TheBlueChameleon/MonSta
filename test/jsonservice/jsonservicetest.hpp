#ifndef JSONSERVICETEST_HPP
#define JSONSERVICETEST_HPP

#include <gtest/gtest.h>

class JsonServiceTest : public testing::Test
{
    protected:
        static void SetUpTestSuite();
        static void TearDownTestSuite();

        void SetUp() override;
        void TearDown() override;
};

#endif // JSONSERVICETEST_HPP
