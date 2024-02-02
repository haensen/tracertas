#ifndef TRACERT_HPP
#define TRACERT_HPP

#include <string>
#include <vector>
#include <functional>

/**
 * Represent one hop on a route
*/
struct Hop {
    std::string address;
    /**
     * Autonomous system number
    */
    int64_t asn;
};

/**
 * Traceroute
 * @param destination
 * @param packetSender Function, check sendPacket below
 * @returns route
*/
std::vector<Hop> tracert(std::string destination, std::function<std::string(std::string, int)> packetSender);

/**
 * Sends a packet to the given address with a given ttl.
 * @param destination IPv4
 * @param ttl Time To Live
 * @returns address where TTL ended, or destination if it got reached.
*/
std::string sendPacket(std::string destination, int ttl);

#endif
