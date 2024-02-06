#include "ip_info.hpp"
#include "address.hpp"
#include "config.hpp"
#include "csv.hpp"

#include <fstream>
#include <iostream>

bool IpInfo::initialized = false;
const int64_t IpInfo::UnknownAsn = -1;
std::map<uint32_t, std::string> IpInfo::asNames;
PrefixContainer<int64_t> IpInfo::asNumbers(IpInfo::UnknownAsn);
PrefixContainer<std::string> IpInfo::ixNames("");

IpInfo::IpInfo() {
    // Load the Prefixes and ASNs only once from the file
    if (!this->initialized) {
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

    std::string addressSpace, asNumber;
    while (!file.eof()) {
        file >> addressSpace;
        file >> asNumber;

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

    CSV csv(file);
    for (long long i = 0; i < csv.rows(); i++) {
        uint32_t asn = std::stoll(csv.cell("asn", i));
        std::string name = csv.cell("description", i);
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
    return "";
}

void IpInfo::initializeIpToIx() {
    // Open the file
    std::ifstream file(IX_IPV4_FILE);
    if (!file.is_open()) {
        std::cout << "Cannot open IX prefix file: " << IX_IPV4_FILE << std::endl;
    }

    CSV csv(file);
    for (long long i = 0; i < csv.rows(); i++) {
        std::string prefix = csv.cell("Prefix", i);
        std::string name = csv.cell("Name", i);
        ixNames.addPrefix(prefix, name);
    }

    file.close();
}

std::string IpInfo::getIx(Ipv4Address addr) {
    return ixNames.getByIp(addr);
}
