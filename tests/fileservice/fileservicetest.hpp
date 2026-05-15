#ifndef FILESERVICETEST_HPP
#define FILESERVICETEST_HPP

#include <gtest/gtest.h>

#include <filesystem>

class FileServiceTest : public testing::Test
{
    protected:
        static std::filesystem::path home;
        static std::filesystem::path temp;

        void SetUp() override;
        static void SetUpTestSuite();
        static void TearDownTestSuite();
};

#endif // FILESERVICETEST_HPP
