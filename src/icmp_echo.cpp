#include "icmp_echo.hpp"
#include "protocol_headers.hpp"
#include "address.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <functional>

using namespace asio;

void IcmpEcho::receivePacket(std::size_t length) {
    // Get the reply
    replyBuffer.commit(length);
    std::istream reply(&replyBuffer);

    // Parse headers
    IPv4Header ipHeader(reply);
    IcmpHeader icmpHeader(reply);

    if (icmpHeader.type() == IcmpHeader::echoReply) {
        if (icmpHeader.identifier() == this->identifier) {
            this->replyAddress = Ipv4Address(ipHeader.source());
        }
    } else if (icmpHeader.type() == IcmpHeader::timeExceeded) {
        // Start of the original packet is included in the icmp tll exceeded message
        IPv4Header originalIpHeader(reply);
        IcmpHeader originalIcmpHeader(reply);

        if (originalIcmpHeader.identifier() == this->identifier) {
            this->replyAddress = Ipv4Address(ipHeader.source());
        }
    } else {
        // This packet was something else: check next packet
        this->replyBuffer.consume(this->replyBuffer.size());
        socket->async_receive(replyBuffer.prepare(65536), std::bind(&IcmpEcho::receivePacket, this, std::placeholders::_2));
    }
}


IcmpEcho::IcmpEcho(Ipv4Address destination, int ttl) {
    // Open the socket
    this->socket = new ip::icmp::socket(ioContext);
    socket->open(ip::icmp::v4());
    socket->set_option(ip::unicast::hops(ttl));

    // craft the icmp packet
    std::stringstream requestBuffer;
    IcmpHeader::buildEchoRequest(this->identifier, this->sequenceNumber, requestBuffer);

    // Send the packet
    ip::icmp::resolver resolver(ioContext);
    ip::icmp::endpoint endpoint = *resolver.resolve(ip::icmp::v4(), destination.asString(), "").begin();
    socket->send_to(asio::buffer(requestBuffer.str()), endpoint);
    socket->async_receive(replyBuffer.prepare(65536), std::bind(&IcmpEcho::receivePacket, this, std::placeholders::_2));

    // Wait for a response, Timeout after 1 second
    ioContext.run_for(std::chrono::milliseconds(1000));

    // Close the socket
    socket->close();
    delete this->socket;
}

Ipv4Address IcmpEcho::returnAddress() {
    return this->replyAddress;
}
