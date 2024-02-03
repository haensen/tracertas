#ifndef TRACETREE_HPP
#define TRACETREE_HPP

#include "tracert.hpp"
#include "address.hpp"

#include <map>
#include <iostream>

/**
 * Represent one hop on a route
*/
struct Hop {
    std::string address;
    /**
     * Autonomous system number
    */
    int64_t asn;

    Hop* previous;
    std::map<Ipv4Address, Hop> nextConnected;
};

class TraceTree {
    Hop root;

    public:
        TraceTree();
        void addRoute(std::vector<std::string> route);
        friend std::ostream& operator<<(std::ostream& os, const TraceTree& tt);
};

#endif
