#include "as_number.hpp"
#include "address.hpp"
#include "config.hpp"

#include <fstream>
#include <iostream>

bool AsNumber::initialized = false;
std::vector<std::map<uint32_t, uint32_t>> AsNumber::ipSpaceToAsn(33);

AsNumber::AsNumber() {
    if (!this->initialized) {
        initialize();
        this->initialized = true;
    }
}

void AsNumber::initialize() {
    // Open the file
    std::ifstream file(ASN_IPV4_MAPPING_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open ASN file: " << ASN_IPV4_MAPPING_FILE << std::endl;
    }

    std::string addressSpace, asNumber;
    while (!file.eof()) {
        file >> addressSpace;
        file >> asNumber;

        // Split for example 127.0.0.0/24 to IP and mask length
        const int delimeterInd = addressSpace.find("/");
        std::string addressStr = addressSpace.substr(0, delimeterInd);
        std::string maskLengthStr = addressSpace.substr(delimeterInd + 1, addressSpace.length());

        // Add the Ip range and Asn to data structure
        uint32_t address = Ipv4Address(addressStr).asUint();
        int maskLength;
        uint32_t asn;
        maskLength = std::stoi(maskLengthStr);
        asn = std::stoul(asNumber);
        this->ipSpaceToAsn[maskLength][address] = asn;
    }


    file.close();
}

uint32_t AsNumber::getI4(std::string ipv4) {
    if (isIpv4Address(ipv4) == false) {
        return -1;
    }

    uint32_t address = Ipv4Address(ipv4).asUint();

    for (int i = 32; i > 0; i--) {
        uint32_t maskedAddress = (0xFFFFFFFF << (32 - i)) & address;
        std::map<uint32_t, uint32_t>::iterator it = this->ipSpaceToAsn[i].find(maskedAddress);
        if (it != this->ipSpaceToAsn[i].end()) {
            return it->second;
        }
    }

    return -1;
}
