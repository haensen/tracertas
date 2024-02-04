#include "cli.hpp"
#include "address.hpp"
#include "dns.hpp"

#include <iostream>

std::stringstream CLI::getUserLine() {
    std::cout << "Cmd: " << std::flush;

    std::string userLineStr;
    std::getline(istream, userLineStr);
    return std::stringstream(userLineStr);
}

void CLI::visualizeRoute(std::vector<std::string> &route) {
    for (std::string hop : route) {
        std::cout << hop << std::endl;
    }
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

            std::vector<std::string> hops = tracert(address.asString(), sendPacket);

            this->visualizeRoute(hops);
            traceTree.addRoute(hops);
        } else if (command == "s") {
            std::cout << traceTree;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}
