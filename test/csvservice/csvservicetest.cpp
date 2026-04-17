#include "csvservice/csvservice.hpp"
#include "csvservice/csvservice_dlx.hpp"

#include "csvservicetest.hpp"

TEST_F(CsvServiceTest, RegularData)
{
    using namespace CsvService;

    auto data = R"("header", "with", "names"
1,0,"string data"
2,,"more stuff")";

    auto cfg = ICsvService::CsvOptions{};
    auto csv = IndexedCsvData(data, "simulated file", cfg);

    csv.reIndexRows(0);

    EXPECT_EQ(3, csv.getRowCount());
    EXPECT_EQ("header", csv.getCell(0, 0));
    EXPECT_EQ("0", csv.getRow("1")[1]);

    EXPECT_EQ(3, csv.getMaxWidth());
}

TEST_F(CsvServiceTest, DlxInterface)
{
    using namespace CsvService;

    auto data = R"("header", "with", "names"
1,0,"string data"
2,,"more stuff")";

    auto cfg = ICsvService::CsvOptions{};
    auto csv = parseCsvData_dlx(data, "simulated file", cfg);

    reIndexRows_dlx(csv, 0);

    EXPECT_EQ(3, getRowCount_dlx(csv));
    auto cell = getCell_dlx(csv, 0, 0);
    EXPECT_STREQ("header", cell.data);

    auto row = reserveRowBuffer_dlx(csv);
    getRowByName_dlx(csv, row, "1");
    EXPECT_STREQ("0", row.data[1].data);

    EXPECT_EQ(3, getMaxWidth_dlx(csv));

    freeRowBuffer_dlx(&row);
    freeCsvData_dlx(&csv);
}
