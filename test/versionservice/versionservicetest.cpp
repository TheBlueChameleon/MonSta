#include <Version.hpp>

#include "versionservice/versionservice.hpp"

#include "versionservicetest.hpp"

TEST_F(VersionServiceTest, CompareValidity)
{
    Version ve1(1,2,3,4);
    Version ve2(1,2,3,4);

    Version vl1(1,2,3,0);
    Version vl2(1,2,0,5);
    Version vl3(1,0,4,5);
    Version vl4(0,3,4,5);

    EXPECT_EQ(ve1, ve2);
    EXPECT_LE(ve1, ve2);
    EXPECT_GE(ve1, ve2);

    EXPECT_LT(vl1, ve1);
    EXPECT_LT(vl2, ve1);
    EXPECT_LT(vl3, ve1);
    EXPECT_LT(vl4, ve1);

    EXPECT_GT(ve1, vl1);
    EXPECT_GT(ve1, vl2);
    EXPECT_GT(ve1, vl3);
    EXPECT_GT(ve1, vl4);
}
