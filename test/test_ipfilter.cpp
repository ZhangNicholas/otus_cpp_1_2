#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "ipfilter.hpp"

TEST(Iplist, Empty) {
    // Arrange
    iplist ip_pool;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(ip_pool.size(), 0);
    ASSERT_TRUE(ip_pool.empty());
}

TEST(Ipist, Size) {
    // Arrange
    int count = 10;
    std::vector<std::string> placeholder{""};
    iplist ip_pool;

    // Act
    for (size_t i = 0; i < count; ++i) {
        ip_pool.push_back(placeholder);
    }

    // Assert
    ASSERT_EQ(ip_pool.size(), count);
    ASSERT_FALSE(ip_pool.empty());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}