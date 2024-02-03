#include "address.hpp"

#include <stdio.h>
#include <sstream>

bool isIpv4Address(std::string str) {
    int a, b, c, d;
    int scanned = sscanf(str.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
    if (scanned != 4) return false;
    if (a < 0 || a > 255) return false;
    if (b < 0 || b > 255) return false;
    if (c < 0 || c > 255) return false;
    if (d < 0 || d > 255) return false;
    return true;
}

Ipv4Address::Ipv4Address(std::string addr) {
    if (addr.length() == 0) return; // set address to 0.0.0.0
    // Safe the given string address to this->address in uint32_t format
    std::string numbers;
    addr += '.';
    for (int i = 0; i < addr.length(); i++) {
        if (addr[i] == '.') {
            uint8_t byte = std::stoi(numbers);
            this->address = this->address << 8 | byte;
            numbers = "";
        } else {
            numbers += addr[i];
        }
    }
}

uint32_t Ipv4Address::asUint() {
    return this->address;
}

Ipv4Address::Ipv4Address(uint32_t address) {
    this->address = address;
}

std::string Ipv4Address::asString() {
    std::stringstream ss;
    ss << ((address >> 24) & 0xFF) << '.';
    ss << ((address >> 16) & 0xFF) << '.';
    ss << ((address >> 8) & 0xFF) << '.';
    ss << (address & 0xFF);
    return ss.str();
}
