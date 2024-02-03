#include <gtest/gtest.h>

#include "../src/tracetree.hpp"

TEST(TraceTree, constructsAndOutputsBasicTree) {
    TraceTree tTree;
    std::vector<std::string> route1 {
        "10.0.0.1",
        "10.0.0.2",
        "10.0.0.3",
        "10.0.0.4",
        "10.0.0.5",
    };
    std::vector<std::string> route2 {
        "10.0.0.1",
        "10.0.0.2",
        "8.8.8.8",
        "192.168.0.1"
    };
    tTree.addRoute(route1);
    tTree.addRoute(route2);

    std::string expectation =
        "Root : -1\n"
        "\t10.0.0.1 : -1\n"
        "\t\t10.0.0.2 : -1\n"
        "\t\t\t8.8.8.8 : 15169\n"
        "\t\t\t\t192.168.0.1 : -1\n"
        "\t\t\t10.0.0.3 : -1\n"
        "\t\t\t\t10.0.0.4 : -1\n"
        "\t\t\t\t\t10.0.0.5 : -1\n";


    std::stringstream ss;
    ss << tTree;

    EXPECT_EQ(expectation, ss.str());
}
