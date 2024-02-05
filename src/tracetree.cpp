#include "tracetree.hpp"
#include "as_number.hpp"

TraceTree::TraceTree() {
    root.address = "This computer";
    root.previous = nullptr;
    root.asn = AsNumber::Unknown;
}

void TraceTree::addRoute(std::vector<std::string> route) {
    Hop* prevHop = &root;
    for (std::string addrStr : route) {
        Ipv4Address address(addrStr);

        // Add the hop to the tree if it wasn't already
        std::map<Ipv4Address,Hop>::iterator hopInTreeIt = prevHop->nextConnected.find(address);
        if (hopInTreeIt == prevHop->nextConnected.end()) {
            Hop hop;
            hop.address = (addrStr == "" ? "Unknown" : addrStr);
            hop.asn = AsNumber().getNumber(addrStr);
            hop.previous = prevHop;
            hopInTreeIt = prevHop->nextConnected.insert({address, hop}).first;
        }

        prevHop = &(hopInTreeIt->second);
    }
}

void recursivePrint(std::ostream& os, const Hop* hop, std::string graphLine, bool isFirst, bool isLast, bool isRoot) {
    // Print the graph
    std::string childGraphLine = graphLine;
    if (!isRoot) {
        os << graphLine;
        if (isFirst) {
            os << "|" << std::endl;
            os << graphLine;
        }

        if (isLast) {
            os << "'";
        } else {
            os << "+";
        }
        os << "--";

        if (isLast) {
            childGraphLine += " ";
        } else {
            childGraphLine += "|";
        }
        childGraphLine += "  ";
    }
    
    // Print info about this hop
    os << hop->address;
    if (hop->asn != AsNumber::Unknown) {
        os << " : AS " << hop->asn;
        os << " " << AsNumber().getName(hop->asn);
    }
    os << std::endl;

    // Print the hops that orginate from this hop
    for (auto nextHopIt = hop->nextConnected.begin(); nextHopIt != hop->nextConnected.end(); nextHopIt++) {
        bool childIsFirst = (nextHopIt == hop->nextConnected.begin());
        bool childIsLast = (nextHopIt != hop->nextConnected.end()) && (nextHopIt == --hop->nextConnected.end());
        recursivePrint(os, &nextHopIt->second, childGraphLine, childIsFirst, childIsLast, false);
    }
}

std::ostream& operator<<(std::ostream& os, const TraceTree& tt) {
    recursivePrint(os, &tt.root, "", false, true, true);
    return os;
}
