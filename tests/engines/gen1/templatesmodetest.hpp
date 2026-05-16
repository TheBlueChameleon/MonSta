#ifndef TEMPLATESMODETEST_HPP
#define TEMPLATESMODETEST_HPP

#include <gtest/gtest.h>

class TemplatesModeTest : public testing::Test
{
    protected:
        TemplatesModeTest() = default;

        static void SetUpTestSuite();
        static void TearDownTestSuite();
};

#endif // TEMPLATESMODETEST_HPP
