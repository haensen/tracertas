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
    std::vector<std::string> route3 {
        "10.0.0.1",
        "",
        "8.8.8.8",
        "192.168.0.1"
    };
    tTree.addRoute(route1);
    tTree.addRoute(route2);
    tTree.addRoute(route3);

    std::string expectation =
        "This computer\n"
        "|\n"
        "'--10.0.0.1\n"
        "   |\n"
        "   +--10.0.0.2\n"
        "   |  |\n"
        "   |  +--8.8.8.8 : AS 15169 Google LLC\n"
        "   |  |  |\n"
        "   |  |  '--192.168.0.1\n"
        "   |  '--10.0.0.3\n"
        "   |     |\n"
        "   |     '--10.0.0.4\n"
        "   |        |\n"
        "   |        '--10.0.0.5\n"
        "   '--Unknown\n"
        "      |\n"
        "      '--8.8.8.8 : AS 15169 Google LLC\n"
        "         |\n"
        "         '--192.168.0.1\n";


    std::stringstream ss;
    ss << tTree;

    EXPECT_EQ(expectation, ss.str());
}
