#include "tracetree.hpp"

#include <sstream>

// This is used to make sure the IP addresses are printed in order
bool TraceTree::Hop::CmpByIpOrStr::operator()(const std::string& a, const std::string& b) const {
    auto convertToIp = [](const std::string& str) {
        std::stringstream ss;
        ss << str;
        if (isIpv4Address(ss.str())) {
            return Ipv4Address(ss.str());
        } else {
            return Ipv4Address::Nonexisting;
        }
    };
    Ipv4Address ipa = convertToIp(a);
    Ipv4Address ipb = convertToIp(b);
    if (ipa == Ipv4Address::Nonexisting || ipb == Ipv4Address::Nonexisting) {
        return a < b;
    } else {
        return ipa < ipb;
    }
}

TraceTree::TraceTree() {
    root.description = "This computer";
    root.previous = nullptr;
}

void TraceTree::addRoute(std::vector<std::string>& route) {
    Hop* prevHop = &root;
    for (std::string description : route) {
        // Add the hop to the tree if it wasn't already
        std::map<std::string,Hop>::iterator hopInTreeIt = prevHop->nextConnected.find(description);
        if (hopInTreeIt == prevHop->nextConnected.end()) {
            Hop hop;
            hop.description = description;
            hop.previous = prevHop;
            hopInTreeIt = prevHop->nextConnected.insert({description, hop}).first;
        }

        prevHop = &(hopInTreeIt->second);
    }
}

void TraceTree::recursivePrint(std::ostream& os, const Hop* hop, std::string graphLine, bool isFirst, bool isLast, bool isRoot) {
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
    os << hop->description << std::endl;

    // Print the hops that orginate from this hop
    for (auto nextHopIt = hop->nextConnected.begin(); nextHopIt != hop->nextConnected.end(); nextHopIt++) {
        bool childIsFirst = (nextHopIt == hop->nextConnected.begin());
        bool childIsLast = (nextHopIt != hop->nextConnected.end()) && (nextHopIt == --hop->nextConnected.end());
        recursivePrint(os, &nextHopIt->second, childGraphLine, childIsFirst, childIsLast, false);
    }
}

std::ostream& operator<<(std::ostream& os, TraceTree& tt) {
    tt.recursivePrint(os, &tt.root, "", false, true, true);
    return os;
}
