#ifndef CLI_HPP
#define CLI_HPP

#include "tracert.hpp"
#include "tracetree.hpp"
#include "address.hpp"

#include <sstream>

/**
 * Class for running a CLI for traceas
*/
class CLI {
    TraceTree traceTree;
    std::istream& istream;

    std::stringstream getUserLine();
    void showRoute(std::vector<std::string> &route);
    std::vector<std::string> descriptiveRoute(std::vector<Ipv4Address> route);
    Ipv4Address getAddress(std::string representation);

    public:
        CLI(std::istream& _istream) : istream(_istream) {}
        /**
         * Run the CLI-program
        */
        void run();
};

#endif
