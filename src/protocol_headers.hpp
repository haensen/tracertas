#ifndef PROTOCOL_HEADERS_HPP
#define PROTOCOL_HEADERS_HPP

#include <iostream>
#include <cstdint>

/**
 * Class for reading IPv4 header according to RFC791
*/
class IPv4Header {
    uint8_t raw[60];

public:
    /**
     * Reads IPv4 header from the given instream. 20 - 60 bytes.
    */
    IPv4Header(std::istream& instream);

    /**
     * Methods for getting the IP-header fields.
     * Check RFC791 for more info.
    */
    uint8_t version() { return this->raw[0] >> 4; }
    uint8_t headerLength() { return (this->raw[0] & 0xF) * 4; }
    uint16_t packetLength() { return (uint16_t)(this->raw[2]) << 8 | this->raw[3]; }
    uint8_t ttl() { return this->raw[8]; }
    uint8_t protocol() { return this->raw[9]; }
    uint16_t checksum() { return (uint16_t)(this->raw[10] << 8 | this->raw[11]); }
    uint32_t source() {
        return
            (uint32_t)(this->raw[12]) << (8*3) |
            (uint32_t)(this->raw[13]) << (8*2) |
            (uint32_t)(this->raw[14]) << (8*1) |
            (uint32_t)(this->raw[15]);
    }
    uint32_t destination() {
        return
            (uint32_t)(this->raw[16]) << (8*3) |
            (uint32_t)(this->raw[17]) << (8*2) |
            (uint32_t)(this->raw[18]) << (8*1) |
            (uint32_t)(this->raw[19]);
    }
};

/**
 * Class for crafting and decoding IPv4 ICMP echo headers.
 * RFC 792
*/
class IcmpHeader {
    uint8_t raw[8];

public:
    enum Type {
        echoReply = 0,
        unreachable = 3,
        redirect = 5,
        echoRequest = 8,
        timeExceeded = 11,
    };

    /**
     * Constructs an ICMP header according to given fields.
     * EchoRequest is the only type guarantied to work.
    */
    IcmpHeader(IcmpHeader::Type type, uint8_t code, uint16_t identifier, uint16_t sequenceNumber);
    /**
     * Reads ICMP header from instream
    */
    IcmpHeader(std::istream& instream);
    /**
     * Writes ICMP header to ostream
    */
    void write(std::ostream& ostream);

    uint8_t type() { return this->raw[0]; }
    uint8_t code() { return this->raw[1]; }
    uint16_t checksum() { return (uint16_t)(this->raw[2]) << 8 | this->raw[3]; }
    uint16_t identifier() { return (uint16_t)(this->raw[4]) << 8 | this->raw[5]; }
    uint16_t sequenceNumber() { return (uint16_t)(this->raw[6]) << 8 | this->raw[7]; }
    uint8_t headerLength() { return 8; }

    /**
     * Constructs icmp echo request with header and data.
     * @param ostream Writes the request to this stream.
    */
    static void buildEchoRequest(uint16_t identifier, uint16_t sequenceNumber, std::ostream& ostream);
};

#endif
