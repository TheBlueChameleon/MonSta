#include "csvservice/csvservice.hpp"

#include "csvservicetest.hpp"

TEST_F(CsvServiceTest, Foo)
{
    using namespace CsvService;

    auto data = R"("header", "with", "names"
1,0,"string data"
2,0,"more stuff"
)";

    IndexedCsvFile(data, "simulated file");
}
