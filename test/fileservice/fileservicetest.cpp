#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

#include "loggerservice/loggerservice.hpp"

#include "fileservice/debugstream.hpp"
#include "fileservice/fileservice.hpp"
#include "fileservice/fileserviceoperations.hpp"
using namespace FileService;
#include "fileservicetest.hpp"

#include "serviceadapters/fileservicedatabaseadapter.hpp"
#include "serviceadapters/loggerserviceadapter.hpp"

std::filesystem::path FileServiceTest::home = std::filesystem::current_path();
std::filesystem::path FileServiceTest::temp = std::filesystem::temp_directory_path() / "FileServiceTest";

void FileServiceTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
    std::filesystem::create_directories(temp);
}

void FileServiceTest::TearDownTestSuite()
{
    FileServiceDatabaseAdapter::getInstance().reset();
    std::filesystem::remove_all(temp);
}

void FileServiceTest::SetUp()
{
    for (const auto& dirEntry : std::filesystem::directory_iterator{temp})
    {
        std::filesystem::remove_all(dirEntry.path());
    }
}

TEST_F(FileServiceTest, IOPaths_Default)
{
    ASSERT_EQ(FileService::getInputBasePath(), home)  <<  "input base path not home directory";
    ASSERT_EQ(FileService::getOutputBasePath(), home) << "output base path not home directory";
}

TEST_F(FileServiceTest, IOPaths_SetExistingAbsolute)
{
    FileService::setInputBasePath(temp);
    FileService::setOutputBasePath(temp);

    ASSERT_EQ(FileService::getInputBasePath(), temp);
    ASSERT_EQ(FileService::getOutputBasePath(), temp);
}

TEST_F(FileServiceTest, IOPaths_SetNonExisting)
{
    // setup
    const std::filesystem::path nonExisting = temp / "valid/relative/path";
    //std::filesystem::create_directories(temp / nonExisting);

    FileService::setInputBasePath(temp);
    FileService::setOutputBasePath(temp);

    // when
    FileService::setInputBasePath(nonExisting);
    FileService::setOutputBasePath(nonExisting);

    // then
    EXPECT_EQ(FileService::getInputBasePath(), temp);
    EXPECT_EQ(FileService::getOutputBasePath(), temp);
}

TEST_F(FileServiceTest, IOPaths_SetNonExistingWithCreate)
{
    // setup
    const std::filesystem::path toBeCreated = temp / "valid/relative/path";

    FileService::setInputBasePath(temp);
    FileService::setOutputBasePath(temp);
    FileService::setCreateDirectories(true);

    // when
    FileService::setInputBasePath(toBeCreated);
    FileService::setOutputBasePath(toBeCreated);

    // then
    EXPECT_EQ(FileService::getInputBasePath(), temp);  // do not create dirs in input space, even with flag!
    EXPECT_EQ(FileService::getOutputBasePath(), toBeCreated);
    EXPECT_TRUE(std::filesystem::exists(toBeCreated));
}

TEST_F(FileServiceTest, SpecialPaths)
{
    EXPECT_EQ(false, FileService::isSpecialPath(""));
    EXPECT_EQ(false, FileService::isSpecialPath("/"));
    EXPECT_EQ(false, FileService::isSpecialPath("C:\\"));
    EXPECT_EQ(false, FileService::isSpecialPath("relative/path"));

    EXPECT_EQ(true, FileService::isSpecialPath(STDOUTSTREAM));
    EXPECT_EQ(true, FileService::isSpecialPath(DEBUGSTREAM));
    EXPECT_EQ(true, FileService::isSpecialPath(NULLSTREAM));

    EXPECT_EQ(true, FileService::isSpecialPath(":stdout:/title"));
    EXPECT_EQ(true, FileService::isSpecialPath("home/:stdout:"));
    EXPECT_EQ(true, FileService::isSpecialPath("home/:stdout:/title"));

    EXPECT_EQ(OutputStreamType::REGULAR, outputStreamTypeFromCString("/"));
    EXPECT_EQ(OutputStreamType::REGULAR, outputStreamTypeFromCString("C:\\"));

    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromCString(""));
    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromCString("::"));
    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromCString(":unknown_symbol:"));

    EXPECT_EQ(OutputStreamType::STDOUT, outputStreamTypeFromCString(STDOUTSTREAM));
    EXPECT_EQ(OutputStreamType::DEBUG, outputStreamTypeFromCString(DEBUGSTREAM));
    EXPECT_EQ(OutputStreamType::NULLSTREAM, outputStreamTypeFromCString(NULLSTREAM));

    std::filesystem::path nullpath;
    std::filesystem::path residual = "residual";
    std::filesystem::path debug = DEBUGSTREAM;
    std::filesystem::path prefixed = std::filesystem::path(DEBUGSTREAM) / residual;
    std::filesystem::path postfixed = std::filesystem::path("home") / DEBUGSTREAM;
    std::filesystem::path infixed = std::filesystem::path("home") / DEBUGSTREAM / residual;
    EXPECT_EQ(
        std::make_pair(OutputStreamType::INVALID, nullpath),
        getOutputStreamTypeAndResidualFilename("")
    );
    EXPECT_EQ(
        std::make_pair(OutputStreamType::REGULAR, residual),
        getOutputStreamTypeAndResidualFilename(residual)
    );
    EXPECT_EQ(
        std::make_pair(OutputStreamType::DEBUG, residual),
        getOutputStreamTypeAndResidualFilename(prefixed)
    );
    EXPECT_EQ(
        std::make_pair(OutputStreamType::DEBUG, nullpath),
        getOutputStreamTypeAndResidualFilename(postfixed)
    );
    EXPECT_EQ(
        std::make_pair(OutputStreamType::DEBUG, residual),
        getOutputStreamTypeAndResidualFilename(infixed)
    );
}

TEST_F(FileServiceTest, OutputOrdering)
{
    auto writer = [](const int id, const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);
        FileService::write(":debug:", std::to_string(id) + ";");
    };

    auto t0 = std::thread(writer, 0, 20ms);
    auto t1 = std::thread(writer, 1, 10ms);
    auto t2 = std::thread(writer, 2,  0ms);

    t0.join();
    t1.join();
    t2.join();

    auto& synchronizedResultStream = FileServiceDatabase::getInstance().getOrCreateStream(":debug:");
    auto* innerResultStream = dynamic_cast<FileService::DebugStream*>(synchronizedResultStream.expose());
    auto result = innerResultStream->str();

    std::string expected = "2;1;0;";

    EXPECT_EQ(result, expected);
}

