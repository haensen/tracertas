#ifndef AS_NUMBER_HPP
#define AS_NUMBER_HPP

#include <string>
#include <vector>
#include <map>

/**
 * A class for checking which Autonomous System owns a given IP address.
*/
class AsNumber {
    static bool initialized;

    // usage: ipSpaceToAsn[maskLengthInBits][ip & mask] = AS number
    static std::vector<std::map<uint32_t, uint32_t>> ipSpaceToAsn;

    void initialize();

    public:
        AsNumber();
        
        /**
         * @returns AS number for the given address or -1 if not found.
        */
        int64_t getI4(std::string ipv4_address);
};

#endif
