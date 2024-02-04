#include <gtest/gtest.h>

#include "../src/dns.hpp"

TEST(DNS, canResolveLocalhost) {
    EXPECT_EQ(DNS().resolve("localhost"), Ipv4Address("127.0.0.1"));
}

TEST(DNS, getsSomeAddressForKnownService) {
    EXPECT_NE(DNS().resolve("google.com"), Ipv4Address::Nonexisting);
}

TEST(DNS, detectsNonExistingHostName) {
    EXPECT_EQ(DNS().resolve("kissa.kissa.koira"), Ipv4Address::Nonexisting);
}
