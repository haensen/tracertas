#ifndef IP_INFO_HPP
#define IP_INFO_HPP

#include "address.hpp"
#include "prefix_container.hpp"

#include <string>
#include <map>

/**
 * A class for getting info about IP addresses such as AS number
*/
class IpInfo {
    static bool initialized;

    static std::map<uint32_t, std::string> asNames;
    static PrefixContainer<int64_t> asNumbers;
    static PrefixContainer<std::string> ixNames;

    void initializeNetworkToAsn();
    void initializeAsToOwner();
    void initializeIpToIx();

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

        /**
         * @returns short string naming the IXP or empty if address is not IX peering router
        */
        std::string getIx(Ipv4Address addr);
};

#endif
