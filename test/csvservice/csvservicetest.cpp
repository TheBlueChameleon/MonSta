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
    auto col = csv.getColumn("header");

    EXPECT_EQ(3, csv.getRowCount());
    EXPECT_EQ("header", csv.getCell(0, 0));
    EXPECT_EQ("0", csv.getRow("1")[1]);
    EXPECT_EQ("header", col[0]);
    EXPECT_EQ("2", col[2]);
    EXPECT_TRUE(csv.hasRow("2"));
    EXPECT_FALSE(csv.hasRow("0"));
    EXPECT_TRUE(csv.hasColumn("header"));
    EXPECT_FALSE(csv.hasColumn("HEADER"));

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
    auto col = getColumnByName_dlx(csv, "header");

    EXPECT_EQ(3, getRowCount_dlx(csv));
    auto cell = getCell_dlx(csv, 0, 0);
    EXPECT_STREQ("header", cell.data);

    auto row = reserveRowBuffer_dlx(csv);
    getRowByName_dlx(csv, row, "1");
    EXPECT_STREQ("0", row.data[1].data);
    EXPECT_STREQ("header", col.data[0].data);
    EXPECT_STREQ("2", col.data[2].data);
    EXPECT_TRUE(hasRow_dlx(csv, "2"));
    EXPECT_FALSE(hasRow_dlx(csv, "0"));
    EXPECT_TRUE(hasColumn_dlx(csv, "header"));
    EXPECT_FALSE(hasColumn_dlx(csv, "HEADER"));

    EXPECT_EQ(3, getMaxWidth_dlx(csv));

    freeColumnBuffer_dlx(&col);
    freeRowBuffer_dlx(&row);
    freeCsvData_dlx(&csv);
}
