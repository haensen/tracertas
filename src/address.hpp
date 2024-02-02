#ifndef ADDRESS_HPP
#define ADDRESS_HPP
#endif

#include <string>

bool isIpv4Address(std::string str);

class Ipv4Address {
    uint32_t address = 0;

    public:
        Ipv4Address(std::string address);

        uint32_t asUint();
};
