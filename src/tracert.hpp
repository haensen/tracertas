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
 * @param packetSender Function, that is given an IPv4 address and ttl, and returns the address where packet got sent back.
 * @returns route
*/
std::vector<Hop> tracert(std::string destination, std::function<std::string(std::string, int)> packetSender);

/**
 * Wrapper around IcmpEcho for tracert
*/
std::string sendPacket(std::string dest, int ttl);

#endif
