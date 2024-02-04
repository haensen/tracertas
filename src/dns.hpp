#ifndef DNS_HPP
#define DNS_HPP

#include "address.hpp"

class DNS {
public:

    /**
     * @returns one IPv4 address where the given host name points to or Ipv4Address::NonExisting if not found.
    */
    Ipv4Address resolve(std::string dnsName);
    // std::string reverseResolve(Ipv4Address ip4);
};

#endif
