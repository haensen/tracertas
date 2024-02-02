#ifndef AS_NUMBER_HPP
#define AS_NUMBER_HPP
#endif

#include <string>
#include <vector>
#include <map>

class AsNumber {
    static bool initialized;

    // usage: ipSpaceToAsn[maskLength][ip & mask] = asn
    static std::vector<std::map<uint32_t, uint32_t>> ipSpaceToAsn;

    void initialize();

    public:
        AsNumber();
        
        int64_t getI4(std::string ipv4_address);
};
