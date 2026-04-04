#include <atomic>
#include <chrono>
#include <cstring>
#include <ostream>
#include <thread>
using namespace std::literals::chrono_literals;

#include <nlohmann/json.hpp>

#include "errors.hpp"

#include "jsonservice/jsonservicedatabase.hpp"

#include "serviceadapters/loggerserviceadapter.hpp"

#include "jsonservicedatabasetest.hpp"

void JsonServiceTest::SetUpTestSuite()
{
    LoggerServiceAdapter::useOnlyTestSink();
}

TEST_F(JsonServiceTest, Database_AddGet_SingleThread)
{
    using namespace JsonService;

    auto instance = JsonServiceDatabase();
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
    const auto raw = R"({"key":"value"})";
    nlohmann::json json = nlohmann::json::parse(raw);

    std::atomic_int writeThrowCount = 0;
    std::atomic_int readThrowCount = 0;
    std::atomic_int readCorrectCount = 0;

    auto instance = JsonServiceDatabase();

    auto writer = [&instance, &tag, &json, &writeThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);


        try
        {
            instance.add(tag, json);
        }
        catch (const LookupError& e)
        {
            ++writeThrowCount;
        }
    };

    auto reader = [&instance, &tag, &raw, &readCorrectCount, &readThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);

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

TEST_F(JsonServiceTest, Database_GetOrAdd)
{
    using namespace JsonService;

    const auto tag = "tag";
    const auto raw = R"({"key":"value"})";

    std::atomic_int correctReads = 0;
    std::atomic_int writeCalls = 0;

    auto instance = JsonServiceDatabase();

    auto creator = [&raw, &writeCalls](nlohmann::ordered_json& target)
    {
        ++writeCalls;
        target = nlohmann::ordered_json::parse(raw);
    };

    auto writer = [&instance, &tag, &raw, &creator, &correctReads]()
    {

        auto json = instance.getOrAdd(tag, creator);

        if (std::strcmp(json.dump().c_str(), raw) == 0)
        {
            ++correctReads;
        }
    };

    auto t1 = std::thread(writer);
    auto t2 = std::thread(writer);

    t1.join();
    t2.join();

    EXPECT_EQ(writeCalls, 1);
    EXPECT_EQ(correctReads, 2);
}

TEST_F(JsonServiceTest, Database_DeclareCommit)
{
    using namespace JsonService;

    const auto tag = "tag";
    const auto key = "key";
    const auto val = "value";
    const auto raw = R"({"key":"value"})";
    nlohmann::json json = nlohmann::json::parse(raw);

    std::atomic_int writeCount = 0;
    std::atomic_int writeThrowCount = 0;
    std::atomic_int readThrowCount = 0;
    std::atomic_int readCorrectCount = 0;

    auto instance = JsonServiceDatabase();

    auto writer = [&instance, &tag, &key, &val, &json, &writeCount, &writeThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(5ms);

        auto data = instance.declare(tag);
        if (data.has_value())
        {
            (data.value().get())[key] = val;
            ++writeCount;
        }

        std::this_thread::sleep_for(delay);

        try
        {
            instance.commit(tag);
        }
        catch (const LookupError& e)
        {
            ++writeThrowCount;
        }
    };

    auto reader = [&instance, &tag, &raw, &readCorrectCount, &readThrowCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);

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

    auto w1 = std::thread(writer, 10ms);        // first commit: succeeds
    auto w2 = std::thread(writer, 20ms);        // second commit: throws

    auto r1 = std::thread(reader,  0ms);        // before write happens: throws
    auto r2 = std::thread(reader, 15ms);        // after write starts
    auto r3 = std::thread(reader, 25ms);        // after write completes

    w1.join();
    w2.join();

    r1.join();
    r2.join();
    r3.join();

    EXPECT_EQ(writeCount, 1);
    EXPECT_EQ(writeThrowCount, 1);
    EXPECT_EQ(readThrowCount, 1);
    EXPECT_EQ(readCorrectCount, 2);
}

TEST_F(JsonServiceTest, Database_DeclareAdd)
{
    using namespace JsonService;

    const auto tag1 = "tag1";
    const auto tag2 = "tag2";
    const auto keyD = "keyD";
    const auto val  = "value";
    const auto rawD = R"({"keyD":"value"})";
    const auto rawA = R"({"keyA":"value"})";

    std::atomic_int declareThrowCount = 0;
    std::atomic_int addThrowCount = 0;
    std::atomic_int readCorrectCount = 0;

    auto instance = JsonServiceDatabase();

    auto declareFirst = [&instance, &tag1, &tag2, &keyD, &val, &rawA, &declareThrowCount, &addThrowCount]()
    {
        std::optional<std::reference_wrapper<nlohmann::ordered_json>> declJsonOpt;

        try
        {
            declJsonOpt = instance.declare(tag1).value();
        }
        catch (const LookupError& e)
        {
            ++declareThrowCount;
        }

        std::this_thread::sleep_for(10ms);

        auto& declJson = declJsonOpt.value().get();
        declJson[keyD] = val;

        try
        {
            instance.add(tag2, declJson);
        }
        catch (const LookupError& e)
        {
            ++declareThrowCount;
        }

        try
        {
            instance.commit(tag1);
        }
        catch (const LookupError& e)
        {
            ++declareThrowCount;
        }
    };

    auto addFirst = [&instance, &tag1, &tag2, &keyD, &val, &rawA, &declareThrowCount, &addThrowCount]()
    {
        try
        {
            instance.add(tag2, nlohmann::json::parse(rawA));
        }
        catch (const LookupError& e)
        {
            ++addThrowCount;
        }

        std::this_thread::sleep_for(10ms);

        try
        {
            auto declJsonOpt = instance.declare(tag1);
            auto& declJson = declJsonOpt.value().get();
            declJson[keyD] = val;
            instance.commit(tag1);
        }
        catch (const LookupError& e)
        {
            ++addThrowCount;
        }
        catch (const std::bad_optional_access& e)
        {
            ++addThrowCount;
        }
    };

    auto readBoth = [&instance, &tag1, &tag2, &rawA, &rawD, &readCorrectCount](const std::chrono::milliseconds delay)
    {
        std::this_thread::sleep_for(delay);

        auto read1 = instance.get(tag1).dump();
        auto read2 = instance.get(tag2).dump();

        if (read1 == rawD)
        {
            readCorrectCount++;
        }
        if (read2 == rawA)
        {
            readCorrectCount++;
        }
    };

    auto w1 = std::thread(declareFirst);
    auto w2 = std::thread(addFirst);

    auto r1 = std::thread(readBoth,  5ms);      // after each thread has finished part 1
    auto r2 = std::thread(readBoth, 15ms);      // after each thread has finished both parts

    w1.join();
    w2.join();

    r1.join();
    r2.join();

    EXPECT_EQ(addThrowCount, 1);
    EXPECT_EQ(declareThrowCount, 1);
    EXPECT_EQ(readCorrectCount, 4);
}
