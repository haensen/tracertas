#include <gtest/gtest.h>

#include "../src/icmp_echo.hpp"

TEST(IcmpEcho, canGetReplyFromLocalhost) {
    EXPECT_EQ(IcmpEcho("127.0.0.1", 10).returnAddress(), "127.0.0.1");
}

TEST(IcmpEcho, getsSomeAddressWhenTTLrunsOut) {
    EXPECT_NE(IcmpEcho("8.8.8.8", 1).returnAddress(), "");
}
