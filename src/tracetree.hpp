#ifndef TRACETREE_HPP
#define TRACETREE_HPP

#include "tracert.hpp"
#include "address.hpp"

#include <map>
#include <iostream>

/**
 * Represent one hop on a route. For internal use of the tracetree.
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

/**
 * Class for displaing traces in a tree format.
*/
class TraceTree {
    Hop root;

    public:
        TraceTree();

        void addRoute(std::vector<std::string> route);

        /**
         * Outputs a human readable representation of the tree
        */
        friend std::ostream& operator<<(std::ostream& os, const TraceTree& tt);
};

#endif
