#include <gtest/gtest.h>

#include "../src/tracert.hpp"

TEST(Tracert, canTraceLocalhost) {
    std::vector<Ipv4Address> trace = tracert(Ipv4Address("127.0.0.1"), sendPacket);
    EXPECT_EQ(trace.size(), 1);
}

TEST(Tracert, canTraceKnownAddress) {
    std::vector<Ipv4Address> trace = tracert(Ipv4Address("8.8.8.8"), sendPacket);
    EXPECT_GE(trace.size(), 3);
}

TEST(Tracert, getsResponseFromLocalhost) {
    EXPECT_EQ(sendPacket(Ipv4Address("127.0.0.1"), 5), Ipv4Address("127.0.0.1"));
}
