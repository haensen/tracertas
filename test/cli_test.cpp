#include <gtest/gtest.h>

#include "../src/cli.hpp"

TEST(CLI, canRunCommandsWithoutCrashing) {
    std::stringstream ss;
    ss << "t 8.8.8.8" << std::endl;
    ss << "t 8.8.4.4" << std::endl;
    ss << "t 1.1.1.1" << std::endl;
    ss << "s" << std::endl;
    ss << "t 2.2.2.2" << std::endl;
    ss << "t google.com" << std::endl;
    ss << "s" << std::endl;
    ss << "exit" << std::endl;
    CLI cli(ss);
    cli.run();
}
