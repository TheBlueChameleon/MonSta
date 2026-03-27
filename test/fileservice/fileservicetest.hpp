#ifndef FILESERVICETEST_HPP
#define FILESERVICETEST_HPP

#include <gtest/gtest.h>

#include <filesystem>
#include <thread>

class FileServiceTest : public testing::Test
{
    protected:
        std::filesystem::path home = std::filesystem::current_path();
        std::filesystem::path temp = std::filesystem::temp_directory_path() / "FileServiceTest";

        FileServiceTest();
        ~FileServiceTest();

        void SetUp() override;
};

#endif // FILESERVICETEST_HPP
