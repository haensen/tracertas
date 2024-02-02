#include <gtest/gtest.h>

#include "../src/as_number.hpp"

TEST(AsNumberTest, ReturnsCorrectAsNumber) {
    EXPECT_EQ(AsNumber().getI4("8.8.8.8"), 15169);
    EXPECT_EQ(AsNumber().getI4("1.0.0.1"), 13335);
    EXPECT_EQ(AsNumber().getI4("223.255.254.8"), 55415);
}

TEST(AsNumberTest, DetectsNonExistingAsnIP) {
    EXPECT_EQ(AsNumber().getI4("kissa"), -1);
    EXPECT_EQ(AsNumber().getI4("127.0.0.1"), -1);
    EXPECT_EQ(AsNumber().getI4("50000"), -1);
}
