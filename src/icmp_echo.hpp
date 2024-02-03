#ifndef ICMP_ECHO_HPP
#define ICMP_ECHO_HPP

#include <asio.hpp>

#include <string>
#include <sstream>

class IcmpEcho {
    asio::ip::icmp::socket* socket;
    asio::io_context ioContext;
    std::string destination;

    uint16_t identifier = 0xbeef;
    uint16_t sequenceNumber = 1;

    asio::streambuf replyBuffer;

    bool received = false;
    std::string replyAddress = "";

    void openSocket();
    void receivePacket(std::size_t length);

public:
    /**
     * Sends a ICMP echo to the given address with a given ttl.
     * @param destination IPv4
     * @param ttl Time To Live
    */
    IcmpEcho(std::string destination, int ttl);

    /**
     * @returns address where TTL ended, or destination if it got reached. Empty if we got no response.
    */
    std::string returnAddress();
};

#endif
