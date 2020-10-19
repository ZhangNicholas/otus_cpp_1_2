#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include"ipfilter.hpp"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

//typedef std::vector < std::vector<std::string> > iplist;
//typedef std::vector<std::string> ip;

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

void print_ip_list(const iplist& vector)
{
    for (auto ip = vector.cbegin(); ip != vector.cend(); ++ip)
    {
        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const* argv[])
{
    try
    {
        iplist ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            ip v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        // required sort
        for (auto i = (size(ip_pool[0]) - 1); i > 0; i--)
        {
            std::stable_sort(ip_pool.begin(), ip_pool.end(), [i](const ip& d1,
                const ip& d2)
                {return stoi(d1[i-1]) > stoi(d2[i-1]);} // that works
            );
        }

        // reverse lexicographical sort
        //for (int i = size(ip_pool[0]) - 1; i >= 0; i--)
        //{
        //    std::stable_sort(ip_pool.begin(), ip_pool.end(), [i](const std::vector<std::string>& d2,
        //        const std::vector<std::string>& d1) {return std::lexicographical_compare(d1[i].begin(), d1[i].end(),
        //            d2[i].begin(), d2[i].end()); });
        //}

        print_ip_list(ip_pool);
        // TODO filter by first byte and output
        // ip = filter(1)
        std::string value = "1";
        int row = 0;

        std::for_each(
            ip_pool.begin(),
            ip_pool.end(),
            [value, row](const ip ip_address) {
                if (ip_address[row] == value) {
                    for (auto ip_part = ip_address.cbegin(); ip_part != ip_address.cend(); ++ip_part)
                    {
                        if (ip_part != ip_address.cbegin())
                        {
                            std::cout << ".";
                        }
                        std::cout << *ip_part;
                    }
                    std::cout << std::endl;
                }

            }
        );

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        value = "46";
        row = 0;
        std::string value1 = "70";
        int row1 = 1;

        std::for_each(
            ip_pool.begin(),
            ip_pool.end(),
            [value, row, value1, row1](const ip ip_address) {
                if ((ip_address[row] == value) & (ip_address[row1] == value1)) {
                    for (auto ip_part = ip_address.cbegin(); ip_part != ip_address.cend(); ++ip_part)
                    {
                        if (ip_part != ip_address.cbegin())
                        {
                            std::cout << ".";
                        }
                        std::cout << *ip_part;
                    }
                    std::cout << std::endl;
                }

            }
        );


        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        value = "46";

        std::for_each(
            ip_pool.begin(),
            ip_pool.end(),
            [value](const ip ip_address) {
                bool value_is_found = false;
                for (auto ip_part = ip_address.cbegin(); ip_part != ip_address.cend(); ++ip_part) {
                    if (!value_is_found) {
                        if (*ip_part == value) {
                            value_is_found = true;
                            for (auto ip_part = ip_address.cbegin(); ip_part != ip_address.cend(); ++ip_part)
                            {
                                if (ip_part != ip_address.cbegin())
                                {
                                    std::cout << ".";
                                }
                                std::cout << *ip_part;
                            }
                            std::cout << std::endl;
                        }
                    }
                    else break;
                }
            }
        );
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}