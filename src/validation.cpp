#include "validation.hpp"

int getValidValue(const std::string& valueAsString) { // check string to consists from digits,
	// first digit is not 0 and value is in range of 0..255
	if (std::all_of(valueAsString.begin(), valueAsString.end(), [](char c) {return isdigit(c); })) {
		int value = stoi(valueAsString);
		if ((value == 0) && (valueAsString.length() > 1)) return -1;
		if ((value >= 0) && (value < 256)) return value;
	}
	return -1;
}

std::vector<uint8_t> extractValidIpV4(const std::vector<std::string>& vector) {
	std::vector<uint8_t> r;
	if (vector.size() == 4) {
		for (const auto ip_byte : vector) {
			int value = getValidValue(ip_byte);
			if (value != -1) r.push_back(static_cast<uint8_t>(value));
			else return {};
		}
		return r;
	}
	return {};
}