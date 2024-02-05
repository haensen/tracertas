#include <gtest/gtest.h>

#include "../src/as_number.hpp"

TEST(AsNumberTest, ReturnsCorrectAsNumber) {
    EXPECT_EQ(AsNumber().getNumber("8.8.8.8"), 15169);
    EXPECT_EQ(AsNumber().getNumber("1.0.0.1"), 13335);
    EXPECT_EQ(AsNumber().getNumber("223.255.254.8"), 55415);
}

TEST(AsNumberTest, DetectsNonExistingAsnIP) {
    EXPECT_EQ(AsNumber().getNumber("kissa"), AsNumber::Unknown);
    EXPECT_EQ(AsNumber().getNumber("127.0.0.1"), AsNumber::Unknown);
    EXPECT_EQ(AsNumber().getNumber("50000"), AsNumber::Unknown);
    EXPECT_EQ((long long)AsNumber().getNumber("50000"), AsNumber::Unknown);
}

TEST(AsNumberTest, ReturnsCorrectName) {
    EXPECT_EQ(AsNumber().getName(15169), "Google LLC");
    EXPECT_EQ(AsNumber().getName(1), "Level 3 Parent, LLC");
    EXPECT_EQ(AsNumber().getName(AsNumber::Unknown), "");
}
