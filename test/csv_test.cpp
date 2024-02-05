#include <gtest/gtest.h>

#include "../src/csv.hpp"

TEST(csv, parseValidCsv) {
    std::stringstream ss;
    ss << "column1,column2,column3" << std::endl;
    ss << "\"cat\",dog,parrot" << std::endl;
    ss << "router,ip,vlan" << std::endl;
    ss << "elephant,car,\"grand , ma\"" << std::endl;
    ss << "vs code,tripl3,Pro Git book" << std::endl;

    CSV csv(ss);
    EXPECT_EQ(csv.columns(), 3);
    EXPECT_EQ(csv.rows(), 4);

    EXPECT_EQ(csv.columnHeader(0), "column1");
    EXPECT_EQ(csv.columnHeader(1), "column2");
    EXPECT_EQ(csv.columnHeader(2), "column3");

    EXPECT_EQ(csv.cell("column1", 0), "cat");
    EXPECT_EQ(csv.cell("column2", 0), "dog");
    EXPECT_EQ(csv.cell("column3", 0), "parrot");

    EXPECT_EQ(csv.cell("column1", 1), "router");
    EXPECT_EQ(csv.cell("column2", 1), "ip");
    EXPECT_EQ(csv.cell("column3", 1), "vlan");

    EXPECT_EQ(csv.cell(0, 2), "elephant");
    EXPECT_EQ(csv.cell(1, 2), "car");
    EXPECT_EQ(csv.cell(2, 2), "grand , ma");

    EXPECT_EQ(csv.cell("column1", 3), "vs code");
    EXPECT_EQ(csv.cell("column2", 3), "tripl3");
    EXPECT_EQ(csv.cell("column3", 3), "Pro Git book");
}
