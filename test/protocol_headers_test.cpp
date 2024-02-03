#include <gtest/gtest.h>

#include "../src/protocol_headers.hpp"

TEST(IPv4Header, Inteprets_ip4_header_correctly) {
    char packet_bytes[] = {
        0x45, 0x30, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00,
        0x3b, 0x01, 0x30, 0xa3, 0x08, 0x08, 0x08, 0x08,
        0xc0, 0xa8, 0x7e, 0x16
    };
    std::stringstream instream;
    instream.write(packet_bytes, 20);
    IPv4Header header(instream);

    EXPECT_EQ(instream.peek(), EOF);

    EXPECT_EQ(header.version(), 4);
    EXPECT_EQ(header.headerLength(), 20);
    EXPECT_EQ(header.packetLength(), 92);
    EXPECT_EQ(header.checksum(), 0x30a3);
    EXPECT_EQ(header.destination(), 0xc0a87e16);
    EXPECT_EQ(header.protocol(), 1);
    EXPECT_EQ(header.source(), 0x08080808);
    EXPECT_EQ(header.ttl(), 59);
}

TEST(IcmpHeader, Inteprets_icmp_header_correctly) {
    char packet_bytes[] = {
        0x00, 0x00, 0x6e, 0xa0, 0x90, 0x5f, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    std::stringstream instream;
    instream.write(packet_bytes, 20);
    IcmpHeader header(instream);

    EXPECT_EQ(header.type(), 0);
    EXPECT_EQ(header.code(), 0);
    EXPECT_EQ(header.checksum(), 0x6ea0);
    EXPECT_EQ(header.identifier(), 0x905f);
    EXPECT_EQ(header.sequenceNumber(), 256);
    EXPECT_EQ(header.headerLength(), 8);
}

TEST(IcmpHeader, constructsCorrectIcmpHeader) {
    IcmpHeader header(IcmpHeader::echoRequest, 0, 0x2348, 0x0100);

    std::stringstream ostream;
    header.write(ostream);

    char packet_bytes[] = {
        0x08, 0x00, 0xd3, 0xb7, 0x23, 0x48, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ((uint8_t)packet_bytes[i], ostream.get());
    }
}

TEST(IcmpHeader, constructsCorrectIcmpEchoRequest) {
    std::stringstream sstream;
    IcmpHeader::buildEchoRequest(0xe14a, 0x0100, sstream);

    char packet_bytes[] = {
        0x08, 0x00, 0x15, 0xb5, 0xe1, 0x4a, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    for (int i = 0; i < (8+64); i++) {
        EXPECT_EQ((uint8_t)packet_bytes[i], sstream.get());
    }
}
