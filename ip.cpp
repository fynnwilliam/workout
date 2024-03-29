#include <iostream>
#include <string>
#include <regex>

bool private_a(std::string const& ip)
{
    std::regex pattern{"([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}"};
    return std::regex_match(ip, pattern);
}

bool private_b(std::string const& ip)
{
    std::regex pattern{"([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip, pattern);
}

bool private_c(std::string const& ip)
{
    std::regex pattern{"([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip, pattern);
}

bool private_ip(std::string const& ip)
{
    return private_a(ip) || private_b(ip) || private_c(ip);
}

bool public_ip(std::string const& ip)
{
    return !private_ip(ip);
}

int main()
{
    std::cout << std::boolalpha << private_ip("8.8.8.8") << '\n'
              << std::boolalpha << public_ip("8.8.8.8")  << std::endl;
}