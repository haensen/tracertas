#ifndef TRACERT_HPP
#define TRACERT_HPP

#include "address.hpp"

#include <string>
#include <vector>
#include <functional>

/**
 * Traceroute
 * @param destination
 * @param packetSender Function, that is given an IPv4 address and ttl, and returns the address where packet got sent back.
 * @returns route
*/
std::vector<Ipv4Address> tracert(Ipv4Address destination, std::function<Ipv4Address(Ipv4Address, int)> packetSender);

/**
 * Wrapper around IcmpEcho for tracert
*/
Ipv4Address sendPacket(Ipv4Address dest, int ttl);

#endif
