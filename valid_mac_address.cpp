#include <iostream>
#include <string>
#include <regex>

bool is_mac_address(std::string item)
{
    std::regex pattern{"((([a-f]|\\d){2}\\:){5}([a-f]|\\d){2})|((([A-F]|\\d){2}\\:){5}([A-F]|\\d){2})"};
    return std::regex_match(item, pattern);
}

int main()
{
    std::cout << std::boolalpha << is_mac_address("2a:27:c7:b7:3d:17") << '\n';
}
