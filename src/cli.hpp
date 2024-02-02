#ifndef CLI_HPP
#define CLI_HPP

#include "tracert.hpp"

#include <sstream>

/**
 * Class for running a CLI for traceas
*/
class CLI {
    std::stringstream getUserLine();
    void visualizeRoute(std::vector<Hop> &route);

    public:
        /**
         * Run the CLI-program
        */
        void run();
};

#endif
