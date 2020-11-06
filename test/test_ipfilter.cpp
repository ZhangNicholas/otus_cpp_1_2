#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "validation.hpp"

bool checkIp(const std::vector<uint8_t>& ip, const std::vector<uint8_t>& expectedIp) {
	if (expectedIp.size() != ip.size()) return false;
	for (int i = 0; i < expectedIp.size(); ++i) {
		if (ip.at(i) != expectedIp.at(i)) return false;
	}
	return true;
}

TEST(getValidValue, validValue) {
	std::string str{ "1" };
	ASSERT_EQ(getValidValue(str), 1);
}
TEST(getValidValue, LeadingZero) {
	std::string str{ "00" };
	ASSERT_EQ(getValidValue(str), -1);
}

TEST(getValidValue, NegativeValue) {
	std::string str{ "-1" };
	ASSERT_EQ(getValidValue(str), -1);
}

TEST(getValidValue, ByteOverflowValue) {
	std::string str{ "256" };
	ASSERT_EQ(getValidValue(str), -1);
}

TEST(getValidValue, nonDigitCharacters) {
	std::string str{ "trololo" };
	ASSERT_EQ(getValidValue(str), -1);
}
TEST(extractValidIpV4, validIP) {
	std::vector<std::string> testStr{ "192", "168", "0", "1" };
	std::vector<uint8_t> expectedIp{ 192, 168, 0, 1 };
	ASSERT_EQ(checkIp(extractValidIpV4(testStr), expectedIp), true);
}

TEST(extractValidIpV4, longIP) {
	std::vector<std::string> testStr{ "192", "168", "0", "1", "0" };
	std::vector<uint8_t> expectedIp{};
	ASSERT_EQ(checkIp(extractValidIpV4(testStr), expectedIp), true);
}

TEST(extractValidIpV4, shortIP) {
	std::vector<std::string> testStr{ "192", "168", "0"};
	std::vector<uint8_t> expectedIp{};
	ASSERT_EQ(checkIp(extractValidIpV4(testStr), expectedIp), true);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}