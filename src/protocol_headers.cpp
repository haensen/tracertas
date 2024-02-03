#include "protocol_headers.hpp"
 
IPv4Header::IPv4Header(std::istream &instream) {
    // Read the first fixed 20 bytes from the header
    instream.read(reinterpret_cast<char*>(this->raw), 20);

    // Read the varying length options
    int optionsLength = this->headerLength() - 20;
    instream.read(reinterpret_cast<char*>(this->raw) + 20, optionsLength);
}

IcmpHeader::IcmpHeader(IcmpHeader::Type type, uint8_t code, uint16_t identifier, uint16_t sequenceNumber) {
    this->raw[0] = type;
    this->raw[1] = code;
    this->raw[4] = identifier >> 8;
    this->raw[5] = identifier & 0xFF;
    this->raw[6] = sequenceNumber >> 8;
    this->raw[7] = sequenceNumber & 0xFF;

    // Calculate the checksum, RFC 1071
    uint32_t checksum = 0;
    checksum += ((uint16_t)raw[0] << 8) + ((uint16_t)raw[4] << 8) + ((uint16_t)raw[6] << 8);
    checksum += (uint16_t)raw[1] + (uint16_t)raw[5] + (uint16_t)raw[7];
    checksum = (checksum >> 16) + (checksum & 0xFFFF);
    checksum = ~checksum;
    this->raw[2] = checksum >> 8;
    this->raw[3] = checksum & 0xFF;
}

IcmpHeader::IcmpHeader(std::istream& instream) {
    instream.read(reinterpret_cast<char*>(this->raw), 8);
}

void IcmpHeader::write(std::ostream& ostream) {
    ostream.write(reinterpret_cast<char*>(this->raw), 8);
}

void IcmpHeader::buildEchoRequest(uint16_t identifier, uint16_t sequenceNumber, std::ostream& ostream) {
    // Write header
    IcmpHeader(IcmpHeader::echoRequest, 0, identifier, sequenceNumber).write(ostream);
    
    // Write data - 64 bytes of zeroes
    char zero[1] = {0};
    for (int i = 0; i < 64; i++) ostream.write(zero, 1);
}
