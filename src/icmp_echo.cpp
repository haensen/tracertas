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
    replyBuffer.commit(length);
    std::istream reply(&replyBuffer);
    IPv4Header ipHeader(reply);
    IcmpHeader icmpHeader(reply);

    if (icmpHeader.type() == IcmpHeader::echoReply) {
        if (icmpHeader.identifier() == this->identifier) {
            this->replyAddress = Ipv4Address(ipHeader.source()).asString();
        }
    } else if (icmpHeader.type() == IcmpHeader::timeExceeded) {
        // Start of the packet is included in the icmp tll exceeded message
        IPv4Header originalIpHeader(reply);
        IcmpHeader originalIcmpHeader(reply);

        if (originalIcmpHeader.identifier() == this->identifier) {
            this->replyAddress = Ipv4Address(ipHeader.source()).asString();
        }
    } else {
        // Not found: Check the next packet
        this->replyBuffer.consume(this->replyBuffer.size());
        socket->async_receive(replyBuffer.prepare(65536), std::bind(&IcmpEcho::receivePacket, this, std::placeholders::_2));
    }
}


IcmpEcho::IcmpEcho(std::string destination, int ttl) : destination(destination) {
    ip::icmp::resolver resolver(ioContext);
    ip::icmp::endpoint endpoint = *resolver.resolve(ip::icmp::v4(), this->destination, "").begin();

    ip::icmp::endpoint localEndpoint(ip::icmp::v4(), 0);

    this->socket = &ip::icmp::socket(ioContext);
    socket->open(ip::icmp::v4());
    socket->set_option(ip::unicast::hops(ttl));

    // craft the icmp packet
    std::stringstream requestBuffer;
    IcmpHeader::buildEchoRequest(this->identifier, this->sequenceNumber, requestBuffer);

    socket->send_to(asio::buffer(requestBuffer.str()), endpoint);
    socket->async_receive(replyBuffer.prepare(65536), std::bind(&IcmpEcho::receivePacket, this, std::placeholders::_2));

    // Wait for a response, Timeout after 1 second
    ioContext.run_for(std::chrono::milliseconds(1000));

    socket->close();
}

std::string IcmpEcho::returnAddress() {
    return this->replyAddress;
}
