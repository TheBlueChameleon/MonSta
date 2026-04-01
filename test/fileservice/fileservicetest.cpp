#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

#include "loggerservice/loggerservice.hpp"

#include "fileservice/debugstream.hpp"
#include "fileservice/fileservice.hpp"
#include "fileservice/fileservicedatabase.hpp"
#include "fileservice/fileserviceoperations.hpp"
#include "fileservice/synchronizedostream.hpp"
using namespace FileService;
#include "fileservicetest.hpp"

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
    std::filesystem::remove_all(temp);
}

void FileServiceTest::SetUp()
{
    FileService::setInputBasePath(temp);
    FileService::setOutputBasePath(temp);

    FileService::setOverwrite(false);
    FileService::setCreateDirectories(false);
    FileService::setDryMode(false);

    for (const auto& dirEntry : std::filesystem::directory_iterator{temp})
    {
        std::filesystem::remove_all(dirEntry.path());
    }
}

// ========================================================================== //

TEST_F(FileServiceTest, IOPaths_SetNonExisting)
{
    // setup
    const std::filesystem::path nonExisting = temp / "valid/relative/path";

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

    EXPECT_EQ(OutputStreamType::REGULAR, outputStreamTypeFromFileName("/"));
    EXPECT_EQ(OutputStreamType::REGULAR, outputStreamTypeFromFileName("C:\\"));

    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromFileName(""));
    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromFileName("::"));
    EXPECT_EQ(OutputStreamType::INVALID, outputStreamTypeFromFileName(":unknown_symbol:"));

    EXPECT_EQ(OutputStreamType::STDOUT,     outputStreamTypeFromFileName(STDOUTSTREAM));
    EXPECT_EQ(OutputStreamType::DEBUG,      outputStreamTypeFromFileName(DEBUGSTREAM));
    EXPECT_EQ(OutputStreamType::NULLSTREAM, outputStreamTypeFromFileName(NULLSTREAM));

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

    auto& synchronizedResultStream = FileService::getDatabase().getOrCreateStream(":debug:");
    auto* innerResultStream = dynamic_cast<FileService::DebugStream*>(synchronizedResultStream.expose());
    auto result = innerResultStream->str();

    std::string expected = "2;1;0;";

    EXPECT_EQ(result, expected);
}
