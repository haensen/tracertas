#include "tracert.hpp"
#include "icmp_echo.hpp"

#include <iostream>

std::vector<std::string> tracert(std::string destination, std::function<std::string(std::string, int)> packetSender) {
    std::vector<std::string> hops;

    const int maxHops = 30;
    for (int i = 0; i < maxHops; i++) {
        std::string responder = packetSender(destination, i);
        hops.push_back(responder);

        if (responder == destination) break;
    }

    // Trim out nonresponsive hosts from the end
    while (hops.back() == "") hops.pop_back();

    return hops;
}

std::string sendPacket(std::string dest, int ttl) {
    IcmpEcho echo(dest, ttl);
    return echo.returnAddress();
}
