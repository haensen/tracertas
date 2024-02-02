#include "tracert.hpp"
#include "as_number.hpp"

#include "icmplib.h"

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

std::string sendPacket(std::string destination, int ttl) {
    icmplib::PingResult result = icmplib::Ping(destination, 1, 1, ttl); // 1 second timeout
    std::cout << (int)result.response << std::endl;

    if (result.response == icmplib::PingResponseType::Success || result.response == icmplib::PingResponseType::TimeExceeded) {
        return result.address;
    }

    return result.address;
}
