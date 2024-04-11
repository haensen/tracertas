#ifndef CONFIG_HPP
#define CONFIG_HPP

// File path to a file containing IPv4 Prefixes and AS numbers
// Can be obtained from:
// https://thyme.apnic.net/current/data-raw-table
// Has to be converted to binary using txt2bin
#define ASN_IPV4_MAPPING_FILE "asPrefixes.bin"

#define ASN_NUMBER_TO_NAME_FILE "asn-info-src/as.csv"

#define IX_IPV4_FILE "ix-networks-src/ix_ip4.csv"

#define ECHO_TIMEOUT_MS 500

#endif
