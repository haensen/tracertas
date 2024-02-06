#ifndef IP_INFO_HPP
#define IP_INFO_HPP

#include "address.hpp"

#include <string>
#include <vector>
#include <map>

/**
 * A class for getting info about IP addresses such as AS number
*/
class IpInfo {
    static bool initialized;

    // usage: ipSpaceToAsn[maskLengthInBits][ip & mask] = AS number
    static std::vector<std::map<uint32_t, uint32_t>> ipSpaceToAsn;
    static std::map<uint32_t, std::string> names;

    void initializeNetworkToAsn();
    void initializeAsToOwner();

    public:
        static const int64_t UnknownAsn;

        IpInfo();
        
        /**
         * @returns AS number for the given address or AsNumber::UnknownAsn if not found.
        */
        int64_t getAsNumber(Ipv4Address ipv4_address);

        /**
         * @returns short string describing the owner of the AS
        */
        std::string getAsName(int64_t asn);
};

#endif
