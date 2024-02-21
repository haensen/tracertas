#ifndef PREFIX_CONTAINER_HPP
#define PREFIX_CONTAINER_HPP

#include "address.hpp"

#include <map>
#include <vector>
#include <cstdint>

/**
 * Stores data about subnets and allows retrieving that data by giving some address in the subnet.
*/
template <typename T> class PrefixContainer {
    T defaultValue;
    
    // Structure: prefixToData[maskLengthInBits][ip & mask] = data
    std::vector<std::map<uint32_t, T>> prefixToData = std::vector<std::map<uint32_t,T>>(33);
public:
    /**
     * @param defaultValue Sets the value that is used when IP doesn't match any prefixes
    */
    PrefixContainer(T defaultValue) : defaultValue(defaultValue) {}

    /**
     * Adds network/prefix to the container
     * @param prefix Ip4 network in CIDR notation eg. 127.0.0.1/24
    */
    void addPrefix(std::string prefix, T data) {
        // Split prefix
        const int delimeterInd = prefix.find("/");
        std::string networkStr = prefix.substr(0, delimeterInd);
        std::string maskLengthStr = prefix.substr(delimeterInd + 1, prefix.length());
        uint32_t network = Ipv4Address(networkStr).asUint();
        int maskLength = std::stoi(maskLengthStr);

        // Add prefix
        prefixToData[maskLength][network] = data;
    }

    /**
     * @returns data from the network where this address is or default if not found
    */
    T getByIp(Ipv4Address addr) {
        for (int maskLength = 32; maskLength > 0; maskLength--) {
            // Create subnet mask for the given address when mask is maskLength bits long
            uint32_t maskedAddress = (0xFFFFFFFF << (32 - maskLength)) & addr.asUint();
            // Check if the masked address corresponds to any prefix
            auto it = prefixToData[maskLength].find(maskedAddress);
            if (it != prefixToData[maskLength].end()) {
                return it->second;
            }
        }

        return defaultValue;
    }
};

#endif
