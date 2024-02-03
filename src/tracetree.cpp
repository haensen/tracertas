#include "tracetree.hpp"
#include "as_number.hpp"

TraceTree::TraceTree() {
    root.address = "Root";
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
            hop.address = addrStr;
            hop.asn = AsNumber().getI4(addrStr);
            hop.previous = prevHop;
            hopInTreeIt = prevHop->nextConnected.insert({address, hop}).first;
        }

        prevHop = &(hopInTreeIt->second);
    }
}

void recursivePrint(std::ostream& os, const Hop* hop, int depth) {
    for (int i = 0; i < depth; i++) os << '\t';
    os << hop->address << " : " << hop->asn << std::endl;

    for (auto nextHopPair : hop->nextConnected) {
        recursivePrint(os, &nextHopPair.second, depth + 1);
    }
}

std::ostream& operator<<(std::ostream& os, const TraceTree& tt) {
    recursivePrint(os, &tt.root, 0);
    return os;
}
