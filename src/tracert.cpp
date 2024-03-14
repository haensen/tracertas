#include "tracert.hpp"
#include "icmp_echo.hpp"

#include <iostream>

std::vector<Ipv4Address> tracert(Ipv4Address destination, std::function<Ipv4Address(Ipv4Address, int)> packetSender) {
    std::vector<Ipv4Address> hops;

    const int maxHops = 30;
    for (int i = 1; i < maxHops; i++) {
        Ipv4Address responder = packetSender(destination, i);
        hops.push_back(responder);

        if (responder == destination) break;
    }

    return hops;
}

Ipv4Address sendPacket(Ipv4Address dest, int ttl) {
    IcmpEcho echo(dest, ttl);
    return echo.returnAddress();
}
