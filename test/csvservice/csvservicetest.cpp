#include "csvservice/csvservice.hpp"

#include "csvservicetest.hpp"

TEST_F(CsvServiceTest, RegularData)
{
    using namespace CsvService;

    auto data = R"("header", "with", "names"
1,0,"string data"
2,,"more stuff"
)";

    auto cfg = ICsvService::CsvOptions{};
    cfg.headerRow = 0;
    cfg.keyColumn = 0;
    auto csv = IndexedCsvData(data, "simulated file", cfg);

    EXPECT_EQ(3, csv.getRowCount());
    EXPECT_EQ("header", csv.getCell(0, 0));
    EXPECT_EQ("0", csv.getRow("1")[1]);

    EXPECT_EQ(3, csv.getMaxWidth());
}
