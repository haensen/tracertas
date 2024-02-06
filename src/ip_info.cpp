#include "ip_info.hpp"
#include "address.hpp"
#include "config.hpp"
#include "csv.hpp"

#include <fstream>
#include <iostream>

bool IpInfo::initialized = false;
std::vector<std::map<uint32_t, uint32_t>> IpInfo::ipSpaceToAsn(33);
std::map<uint32_t, std::string> IpInfo::names;
const int64_t IpInfo::UnknownAsn = -1;

IpInfo::IpInfo() {
    // Load the Prefixes and ASNs only once from the file
    if (!this->initialized) {
        initializeNetworkToAsn();
        initializeAsToOwner();
        this->initialized = true;
    }
}

void IpInfo::initializeNetworkToAsn() {
    // Open the file
    std::ifstream file(ASN_IPV4_MAPPING_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open ASN file: " << ASN_IPV4_MAPPING_FILE << std::endl;
    }

    std::string addressSpace, asNumber;
    while (!file.eof()) {
        file >> addressSpace;
        file >> asNumber;

        // Split prefix for example 127.0.0.0/24 to IP and mask length
        const int delimeterInd = addressSpace.find("/");
        std::string addressStr = addressSpace.substr(0, delimeterInd);
        std::string maskLengthStr = addressSpace.substr(delimeterInd + 1, addressSpace.length());

        // Add the Ip prefix and Asn to data structure
        uint32_t address = Ipv4Address(addressStr).asUint();
        int maskLength = std::stoi(maskLengthStr);
        uint32_t asn = std::stoul(asNumber);
        this->ipSpaceToAsn[maskLength][address] = asn;
    }

    file.close();
}

void IpInfo::initializeAsToOwner() {
    // Open the file
    std::ifstream file(ASN_NUMBER_TO_NAME_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open ASN file: " << ASN_NUMBER_TO_NAME_FILE << std::endl;
    }

    CSV csv(file);
    for (long long i = 0; i < csv.rows(); i++) {
        uint32_t asn = std::stoll(csv.cell("asn", i));
        std::string name = csv.cell("description", i);
        names[asn] = name;
    }

    file.close();
}

int64_t IpInfo::getAsNumber(Ipv4Address ipv4) {
    uint32_t address = Ipv4Address(ipv4).asUint();
    
    for (int i = 32; i > 0; i--) {
        // Create subnet mask for the given address when mask is i bits long
        uint32_t maskedAddress = (0xFFFFFFFF << (32 - i)) & address;
        // Check if the masked address corresponds to any AS prefix
        std::map<uint32_t, uint32_t>::iterator it = this->ipSpaceToAsn[i].find(maskedAddress);
        if (it != this->ipSpaceToAsn[i].end()) {
            return it->second;
        }
    }

    return IpInfo::UnknownAsn;
}

std::string IpInfo::getAsName(int64_t asn) {
    auto iter = names.find(asn);
    if (iter != names.end()) {
        return iter->second;
    }
    return "";
}
