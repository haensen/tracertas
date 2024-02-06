#include <gtest/gtest.h>

#include "../src/icmp_echo.hpp"

TEST(IcmpEcho, canGetReplyFromLocalhost) {
    EXPECT_EQ(IcmpEcho(Ipv4Address("127.0.0.1"), 10).returnAddress(), Ipv4Address("127.0.0.1"));
}

TEST(IcmpEcho, getsSomeAddressWhenTTLrunsOut) {
    EXPECT_NE(IcmpEcho(Ipv4Address("8.8.8.8"), 1).returnAddress(), Ipv4Address::Nonexisting);
}
