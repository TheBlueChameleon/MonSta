#include "fileservice/synchronizedostream.hpp"
#include "fileservice/fileservicedatabase.hpp"

#include "serviceadapters/loggerserviceadapter.hpp"

#include "fileservicedatabasetest.hpp"

std::filesystem::path FileServiceDatabaseTest::home = std::filesystem::current_path();
std::filesystem::path FileServiceDatabaseTest::temp = std::filesystem::temp_directory_path() / "FileServiceTest";

void FileServiceDatabaseTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
    std::filesystem::create_directories(temp);
}

void FileServiceDatabaseTest::TearDownTestSuite()
{
    std::filesystem::remove_all(temp);
}

TEST_F(FileServiceDatabaseTest, DefaultValues)
{
    // setup
    auto database = FileService::FileServiceDatabase();

    // expect
    ASSERT_EQ(database.getInputBasePath(), home)  <<  "input base path not home directory";
    ASSERT_EQ(database.getOutputBasePath(), home) << "output base path not home directory";

    ASSERT_EQ(database.getOverwrite(), false);
    ASSERT_EQ(database.getCreateDirectories(), false);
    ASSERT_EQ(database.getDryMode(), false);
}

TEST_F(FileServiceDatabaseTest, IOPaths_SetExistingAbsolute)
{
    // setup
    auto database = FileService::FileServiceDatabase();

    // when
    database.setInputBasePath(temp);
    database.setOutputBasePath(temp);

    // then
    ASSERT_EQ(database.getInputBasePath(), temp);
    ASSERT_EQ(database.getOutputBasePath(), temp);
}
