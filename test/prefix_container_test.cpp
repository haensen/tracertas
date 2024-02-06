#include <gtest/gtest.h>

#include "../src/prefix_container.hpp"

TEST(PrefixContainer, returnsCorrectData) {
    PrefixContainer<int> pc(1);
    pc.addPrefix("10.0.0.0/24", 2);
    EXPECT_EQ(pc.getByIp(Ipv4Address("10.0.0.1")), 2);
    EXPECT_EQ(pc.getByIp(Ipv4Address("12.0.0.1")), 1);
    EXPECT_EQ(pc.getByIp(Ipv4Address("10.0.0.255")), 2);
    EXPECT_EQ(pc.getByIp(Ipv4Address("10.0.10.1")), 1);
}
