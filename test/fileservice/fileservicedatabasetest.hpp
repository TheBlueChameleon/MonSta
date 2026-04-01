#ifndef FILESERVICEDATABASETEST_HPP
#define FILESERVICEDATABASETEST_HPP

#include <gtest/gtest.h>

class FileServiceDatabaseTest : public testing::Test
{
    protected:
        static std::filesystem::path home;
        static std::filesystem::path temp;

        FileServiceDatabaseTest() = default;

        static void SetUpTestSuite();
        static void TearDownTestSuite();
};

#endif // FILESERVICEDATABASETEST_HPP
