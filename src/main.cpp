// another test travis deploy settings
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "validation.hpp"

std::vector<std::string> split(const std::string& str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}
	r.push_back(str.substr(start));
	return r;
}

std::ostream& operator<< (std::ostream& out, const std::vector<uint8_t>& vector)
{
	for (auto ip_part = vector.cbegin(); ip_part != vector.cend(); ++ip_part) {
		if (ip_part != vector.cbegin()) {
			out << ".";
		}
		out << +*ip_part;
	}
	return out;
}

int main()
{
	try
	{
		std::vector < std::vector<uint8_t> > ipPool;
		int *pLineNumber = new int(0);

		for (std::string line; std::getline(std::cin, line);) {
			std::vector<uint8_t> tempIp{ extractValidIpV4(split(split(line, '\t').at(0), '.')) };
			if (!tempIp.empty()) ipPool.push_back(tempIp);
			else std::cout << "Invalid value '" << line <<"' in line " << *pLineNumber << ". The value was ommitted." << std::endl;
			++*pLineNumber;
		}
		delete pLineNumber;

		std::sort(ipPool.begin(), ipPool.end(), [](const std::vector<uint8_t>& d1,
			const std::vector<uint8_t>& d2) {
				for (int i = 0; i < d1.size(); ++i) {
					if (d1[i] != d2[i]) return d1[i] > d2[i];
				}
				return false;
			}
		); 
	
		for (auto ip : ipPool) {
			std::cout << ip << std::endl;
		}

		std::for_each(
			ipPool.begin(),
			ipPool.end(),
			[](const std::vector<uint8_t> ip) {
				if (ip[0] == 1) {
					std::cout << ip << std::endl;
				}
			}
		);

		std::for_each(
			ipPool.begin(),
			ipPool.end(),
			[](const std::vector<std::uint8_t> ip) {
				if (ip[0] == 46 && ip[1] == 70) {
					std::cout << ip << std::endl;
				}
			}
		);

		std::for_each(
			ipPool.begin(),
			ipPool.end(),
			[](const std::vector<uint8_t> ip) {
				for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
					if (*ip_part == 46) {
						std::cout << ip << std::endl;
						break;
					}
				}
			}
		);
	}

	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}