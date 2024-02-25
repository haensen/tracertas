#ifndef TRACETREE_HPP
#define TRACETREE_HPP

#include "tracert.hpp"
#include "address.hpp"

#include <map>
#include <iostream>

/**
 * Class for displaying traces in a tree format.
*/
class TraceTree {
    /**
     * Represent one hop on the tree.
    */
    struct Hop {
        std::string description;

        Hop* previous;
        struct CmpByIpOrStr {
            bool operator()(const std::string& a, const std::string& b) const;
        };
        std::map<std::string, Hop, Hop::CmpByIpOrStr> nextConnected;
    };

    Hop root;

    void recursivePrint(std::ostream& os, const Hop* hop, const std::string& graphLine, bool isFirst, bool isLast, bool isRoot);

public:
    TraceTree();

    void addRoute(const std::vector<std::string>& route);

    /**
     * Outputs a human readable representation of the tree
    */
    friend std::ostream& operator<<(std::ostream& os, TraceTree& tt);
};

#endif
