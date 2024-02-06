#include <gtest/gtest.h>

#include "../src/ip_info.hpp"

TEST(IpInfo, ReturnsCorrectAsNumber) {
    EXPECT_EQ(IpInfo().getAsNumber(Ipv4Address("8.8.8.8")), 15169);
    EXPECT_EQ(IpInfo().getAsNumber(Ipv4Address("1.0.0.1")), 13335);
    EXPECT_EQ(IpInfo().getAsNumber(Ipv4Address("223.255.254.8")), 55415);
}

TEST(IpInfo, DetectsNonExistingAsnIP) {
    EXPECT_EQ(IpInfo().getAsNumber(Ipv4Address("127.0.0.1")), IpInfo::UnknownAsn);
}

TEST(IpInfo, ReturnsCorrectAsName) {
    EXPECT_EQ(IpInfo().getAsName(15169), "Google LLC");
    EXPECT_EQ(IpInfo().getAsName(1), "Level 3 Parent, LLC");
    EXPECT_EQ(IpInfo().getAsName(IpInfo::UnknownAsn), "");
}

TEST(IpInfo, ReturnsCorrectIxpName) {
    EXPECT_EQ(IpInfo().getIx(Ipv4Address("80.249.208.1")), "AMS-IX v4");
    EXPECT_EQ(IpInfo().getIx(Ipv4Address("127.0.0.1")), "");
    EXPECT_EQ(IpInfo().getIx(Ipv4Address("193.110.224.1")), "FICIX2");
}
