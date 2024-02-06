#ifndef ICMP_ECHO_HPP
#define ICMP_ECHO_HPP

#include "address.hpp"

#include <asio.hpp>

#include <string>
#include <sstream>

class IcmpEcho {
    asio::ip::icmp::socket* socket;
    asio::io_context ioContext;

    uint16_t identifier = 0xbeef;
    uint16_t sequenceNumber = 1;

    asio::streambuf replyBuffer;

    bool received = false;
    Ipv4Address replyAddress = Ipv4Address::Nonexisting;

    void openSocket();
    void receivePacket(std::size_t length);

public:
    /**
     * Sends a ICMP echo to the given address with a given ttl.
     * @param destination IPv4
     * @param ttl Time To Live
    */
    IcmpEcho(Ipv4Address destination, int ttl);

    /**
     * @returns address where TTL ended, or destination if it got reached. IPv4Address::Nonexisting if we did not get response.
    */
    Ipv4Address returnAddress();
};

#endif
