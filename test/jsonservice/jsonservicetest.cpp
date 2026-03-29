#include <atomic>
#include <chrono>
#include <ostream>
#include <thread>
using namespace std::literals::chrono_literals;

#include <nlohmann/json.hpp>

#include "errors.hpp"

#include "jsonservice/jsonservicedatabase.hpp"

#include "serviceadapters/loggerserviceadapter.hpp"
#include "serviceadapters/jsonservicedatabaseadapter.hpp"

#include "jsonservicetest.hpp"

void JsonServiceTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
}

void JsonServiceTest::TearDownTestSuite()
{
    JsonServiceDatabaseAdapter::getInstance().reset();
}

void JsonServiceTest::SetUp()
{
    JsonServiceDatabaseAdapter::getInstance().reset();
}

void JsonServiceTest::TearDown()
{}

TEST_F(JsonServiceTest, Database_AddGet_SingleThread)
{
    using namespace JsonService;

    auto& instance = JsonServiceDatabase::getInstance();
    nlohmann::json json = R"({"key" : "value"})"_json;
    const auto tag = "tag";
    const auto nonexistent = "nonexistent";

    // tag can be added once ...
    EXPECT_NO_THROW(instance.add(tag, json));

    // ... but not twice
    EXPECT_THROW(instance.add(tag, json), LookupError);

    // tag can be read arbitrarily often ...
    const nlohmann::json& ref1 = instance.get(tag);
    const nlohmann::json& ref2 = instance.get(tag);

    // ... and produces the same, correct result every time
    std::ostringstream oss0 {json.dump()};
    std::ostringstream oss1 {ref1.dump()};
    std::ostringstream oss2 {ref2.dump()};

    EXPECT_EQ(oss1.str(), oss0.str());
    EXPECT_EQ(oss2.str(), oss1.str());

    // the original data was copied into the database; further changes do not affect the database
    json["newItem"] = 0;

    const nlohmann::json& ref3 = instance.get(tag);
    std::ostringstream oss3 {ref3.dump()};

    EXPECT_EQ(oss3.str(), oss2.str());
}

TEST_F(JsonServiceTest, Database_AddGet_MultiThread)
{
    using namespace JsonService;

    const auto tag = "tag";
    const auto raw = R"({"KEY":"value"})";
    nlohmann::json json = nlohmann::json::parse(raw);

    std::atomic_int writeThrowCount = 0;
    std::atomic_int readThrowCount = 0;
    std::atomic_int readCorrectCount = 0;

    auto writer = [&tag, &json, &writeThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);

        auto& instance = JsonServiceDatabase::getInstance();
        try
        {
            instance.add(tag, json);
        }
        catch (const LookupError& e)
        {
            ++writeThrowCount;
        }
    };

    auto reader = [&tag, &raw, &readCorrectCount, &readThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);

        auto& instance = JsonServiceDatabase::getInstance();
        try
        {
            const auto result = instance.get(tag);
            if (result.dump() == raw)
            {
                ++readCorrectCount;
            }
        }
        catch (const LookupError& e)
        {
            ++readThrowCount;
        }
    };

    // only one thread may write a given tag
    // any thread can read the same tag

    auto w1 = std::thread(writer, 10ms);
    auto w2 = std::thread(writer, 20ms);

    auto r1 = std::thread(reader,  0ms);        // before write happens
    auto r2 = std::thread(reader, 15ms);        // after write
    auto r3 = std::thread(reader, 25ms);        // after write

    w1.join();
    w2.join();

    r1.join();
    r2.join();
    r3.join();

    EXPECT_EQ(writeThrowCount, 1);
    EXPECT_EQ(readThrowCount, 1);
    EXPECT_EQ(readCorrectCount, 2);
}
