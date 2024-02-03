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

    std::stringstream getUserLine();
    void visualizeRoute(std::vector<std::string> &route);

    std::istream& istream;

    public:
        CLI(std::istream& _istream) : istream(_istream) {}
        /**
         * Run the CLI-program
        */
        void run();
};

#endif
