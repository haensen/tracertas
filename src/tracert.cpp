#include "tracert.hpp"
#include "as_number.hpp"
#include "icmp_echo.hpp"

#include <iostream>

std::vector<Hop> tracert(std::string destination, std::function<std::string(std::string, int)> packetSender) {
    std::vector<Hop> hops;

    const int maxHops = 30;
    for (int i = 0; i < maxHops; i++) {
        std::string responder = packetSender(destination, i);

        Hop currentHop;
        currentHop.address = responder;
        currentHop.asn = AsNumber().getI4(responder);
        hops.push_back(currentHop);

        if (responder == destination) break;
    }

    return hops;
}

std::string sendPacket(std::string dest, int ttl) {
    IcmpEcho echo(dest, ttl);
    return echo.returnAddress();
}
