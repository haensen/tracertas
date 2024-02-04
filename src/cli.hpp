#ifndef CLI_HPP
#define CLI_HPP

#include "tracert.hpp"
#include "tracetree.hpp"

#include <sstream>

/**
 * Class for running a CLI for traceas
*/
class CLI {
    TraceTree traceTree;
    std::istream& istream;

    std::stringstream getUserLine();
    void visualizeRoute(std::vector<std::string> &route);
    Ipv4Address getAddress(std::string representation);

    public:
        CLI(std::istream& _istream) : istream(_istream) {}
        /**
         * Run the CLI-program
        */
        void run();
};

#endif
