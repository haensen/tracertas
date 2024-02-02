#include <gtest/gtest.h>

#include "../src/address.hpp"

TEST(AddressTest, convertsIpToUint32) {
    EXPECT_EQ(Ipv4Address("1.0.0.1").asUint(), 0x01000001);
    EXPECT_EQ(Ipv4Address("10.9.0.0").asUint(), 0x0A090000);
}

TEST(AddressTest, ValidatesIpFormat) {
    EXPECT_EQ(isIpv4Address("1.0.0.1"), true);
    EXPECT_EQ(isIpv4Address("kala"), false);
}
