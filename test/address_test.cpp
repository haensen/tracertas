#include <gtest/gtest.h>

#include "../src/address.hpp"

TEST(Address, convertsIpToUint32) {
    EXPECT_EQ(Ipv4Address("1.0.0.1").asUint(), 0x01000001);
    EXPECT_EQ(Ipv4Address("10.9.0.0").asUint(), 0x0A090000);
}

TEST(Address, convertsUint32toStringRepresentation) {
    EXPECT_STREQ(Ipv4Address(0x01000001).asString().c_str(), "1.0.0.1");
    EXPECT_STREQ(Ipv4Address(0x0A090000).asString().c_str(), "10.9.0.0");
}

TEST(Address, ValidatesIpFormat) {
    EXPECT_EQ(isIpv4Address("1.0.0.1"), true);
    EXPECT_EQ(isIpv4Address("kala"), false);
}
