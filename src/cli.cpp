#include "cli.hpp"
#include "address.hpp"

#include <iostream>

std::stringstream CLI::getUserLine() {
    std::cout << "Cmd: " << std::flush;

    std::string userLineStr;
    std::getline(std::cin, userLineStr);
    return std::stringstream(userLineStr);
}

void CLI::visualizeRoute(std::vector<Hop> &route) {
    for (Hop hop : route) {
        std::cout << hop.asn << '\t' << hop.address << std::endl;
    }
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
            std::string address;
            userLine >> address;
            if (!isIpv4Address(address)) {
                std::cout << "Not valid IPv4 address." << std::endl;
                continue;
            }

            std::vector<Hop> hops = tracert(address, sendPacket);

            this->visualizeRoute(hops);
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}
