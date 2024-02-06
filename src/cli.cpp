#include "cli.hpp"
#include "dns.hpp"
#include "ip_info.hpp"

#include <iostream>
#include <sstream>

std::stringstream CLI::getUserLine() {
    std::cout << "Cmd: " << std::flush;

    std::string userLineStr;
    std::getline(istream, userLineStr);
    return std::stringstream(userLineStr);
}

void CLI::showRoute(std::vector<std::string> &route) {
    for (std::string hop : route) {
        std::cout << hop << std::endl;
    }
}

/**
 * @returns Same route with more info
*/
std::vector<std::string> CLI::descriptiveRoute(std::vector<Ipv4Address> route) {
    std::vector<std::string> descriptive;
    for (auto hop : route) {
        std::stringstream hopDesc;

        if (hop == Ipv4Address::Nonexisting) {
            hopDesc << "Unknown";
        } else {
            hopDesc << hop.asString();

            int64_t asn = IpInfo().getAsNumber(hop);
            if (asn != IpInfo::UnknownAsn) {
                hopDesc << " :AS: " << asn << " " << IpInfo().getAsName(asn);
            }

            std::string ix = IpInfo().getIx(hop);
            if (ix != "") {
                hopDesc << " :IX: " << ix;
            }
        }

        descriptive.push_back(hopDesc.str());
    }
    return descriptive;
}

/**
 * Converts DNS name or IPv4 address to IPv4Address
*/
Ipv4Address CLI::getAddress(std::string representation) {
    if (isIpv4Address(representation)) return Ipv4Address(representation);
    return DNS().resolve(representation);
}

void CLI::run() {
    bool running = true;
    while (running) {
        std::stringstream userLine = this->getUserLine();

        std::string command;
        userLine >> command;

        if (command == "exit" || command == "quit") {
            running = false;
        } else if (command == "t") {
            std::string addressStr;
            userLine >> addressStr;

            Ipv4Address address = getAddress(addressStr);

            if (address == Ipv4Address::Nonexisting) {
                std::cout << "Not valid IPv4 address or host name." << std::endl;
                continue;
            }

            std::vector<Ipv4Address> hops = tracert(address, sendPacket);
            std::vector<std::string> descRoute = descriptiveRoute(hops);
            // Trim out nonresponsive hosts from the end
            bool destinationReached = true;
            while (descRoute.back() == "Unknown") {
                descRoute.pop_back();
                destinationReached = false;
            }


            this->showRoute(descRoute);
            if (!destinationReached) {
                std::cout << "Responses got lost after this point." << std::endl;
            }
            std::cout << std::endl;

            traceTree.addRoute(descRoute);
        } else if (command == "s") {
            std::cout << traceTree;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}
