#include "dns.hpp"

#include <asio.hpp>

Ipv4Address DNS::resolve(std::string dnsName) {
    try {
        // Query the addresses
        asio::io_context ioContext;
        asio::ip::tcp::resolver resolver(ioContext);
        asio::ip::tcp::resolver::results_type results = resolver.resolve(dnsName, "http");

        // Return the first address that is IPv4
        for (auto entry : results) {
            if (entry.endpoint().address().is_v4()) {
                return Ipv4Address(entry.endpoint().address().to_string());
            }
        }
    } catch (const asio::system_error& e) {
        // This is thrown if the host name doesn't exist
    }

    // Not found
    return Ipv4Address::Nonexisting;
}
