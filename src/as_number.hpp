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
    static std::map<uint32_t, std::string> names;

    void initializeNetworkToAsn();
    void initializeAsToOwner();

    public:
        static const int64_t Unknown;

        AsNumber();
        
        /**
         * @returns AS number for the given address or AsNumber::Unknown if not found.
        */
        int64_t getNumber(std::string ipv4_address);

        /**
         * @returns short string describing the owner of the AS
        */
        std::string getName(int64_t asn);
};

#endif
