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
    void showRoute(const std::vector<std::string>& route);
    std::vector<std::string> descriptiveRoute(const std::vector<Ipv4Address>& route);
    Ipv4Address getAddress(const std::string& representation);

public:
    /**
     * @param _istream User input
    */
    CLI(std::istream& _istream) : istream(_istream) {}

    /**
     * Run the CLI
    */
    void run();
};

#endif
