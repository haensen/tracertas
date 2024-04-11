#include "ip_info.hpp"
#include "address.hpp"
#include "config.hpp"
#include "csv.hpp"

#include <fstream>
#include <iostream>

bool IpInfo::initialized = false;
const int64_t IpInfo::UnknownAsn = -1;
std::map<int64_t, std::string> IpInfo::asNames;
PrefixContainer<int64_t> IpInfo::asNumbers(IpInfo::UnknownAsn);
PrefixContainer<std::string> IpInfo::ixNames("");

IpInfo::IpInfo() {
    // Load the Prefixes and ASNs only once from the file
    if (!this->initialized) {
        std::ios::sync_with_stdio(false);
        initializeNetworkToAsn();
        initializeAsToOwner();
        initializeIpToIx();
        this->initialized = true;
    }
}

void IpInfo::initializeNetworkToAsn() {
    // Open the file
    std::ifstream file(ASN_IPV4_MAPPING_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open ASN file: " << ASN_IPV4_MAPPING_FILE << std::endl;
    }

    // Parse networks and as numbers
    std::string addressSpace, asNumber;
    while (file >> addressSpace && file >> asNumber) {
        uint32_t asn = std::stoul(asNumber);
        asNumbers.addPrefix(addressSpace, asn);
    }

    file.close();
}

void IpInfo::initializeAsToOwner() {
    // Open the file
    std::ifstream file(ASN_NUMBER_TO_NAME_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open ASN file: " << ASN_NUMBER_TO_NAME_FILE << std::endl;
    }

    // Parse AS numbers and names
    CSV csv(file);
    int64_t asnColumn = csv.columnIndex(std::string("asn"));
    int64_t nameColumn = csv.columnIndex(std::string("description"));
    for (uint32_t i = 0; i < csv.rows(); i++) {
        uint32_t asn = std::stoul(csv.cell(asnColumn, i));
        std::string name = csv.cell(nameColumn, i);
        asNames[asn] = name;
    }

    file.close();
}

int64_t IpInfo::getAsNumber(Ipv4Address ipv4) {
    return asNumbers.getByIp(ipv4);
}

std::string IpInfo::getAsName(int64_t asn) {
    auto iter = asNames.find(asn);
    if (iter != asNames.end()) {
        return iter->second;
    }
    // Not found
    return "";
}

void IpInfo::initializeIpToIx() {
    // Open the file
    std::ifstream file(IX_IPV4_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open IX prefix file: " << IX_IPV4_FILE << std::endl;
    }

    // Parse networks and ix names
    CSV csv(file);
    int64_t prefixIndex = csv.columnIndex(std::string("Prefix"));
    int64_t nameIndex = csv.columnIndex(std::string("Name"));
    for (uint32_t i = 0; i < csv.rows(); i++) {
        std::string prefix = csv.cell(prefixIndex, i);
        std::string name = csv.cell(nameIndex, i);
        ixNames.addPrefix(prefix, name);
    }

    file.close();
}

std::string IpInfo::getIx(Ipv4Address addr) {
    return ixNames.getByIp(addr);
}
