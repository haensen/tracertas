#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <string>

/**
 * @param str IPv4 address to check
 * @returns True if the given string is a valid IPv4 address.
*/
bool isIpv4Address(std::string str);

/**
 * A Class for representing a IPv4 address.
*/
class Ipv4Address {
    uint32_t address = 0;

    public:
        /**
         * @param address The IPv4 Address in the most common format. Eg: 127.0.0.1
        */
        Ipv4Address(std::string address);

        /**
         * @param address IPv4 address as uint32_t
        */
        Ipv4Address(uint32_t address);

        /**
         * @returns The Ipv4 address as uint32_t so that the first quad of the address is the highest byte.
        */
        uint32_t asUint();

        /**
         * @returns String representation of the address eg. "192.0.0.1"
        */
        std::string asString();

        bool operator<(const Ipv4Address& rhs) const {
            return address < rhs.address;
        }
};

#endif
