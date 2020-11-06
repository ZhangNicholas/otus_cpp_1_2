#pragma once
#include <string>
#include <vector>
#include <algorithm>

int getValidValue(const std::string& valueAsString);
std::vector<uint8_t> extractValidIpV4(const std::vector<std::string>& vector);