#include <iostream>
#include <regex>

bool is_mac_address(std::string_view item)
{
    static const std::regex pattern{"((([a-fA-F]|\\d){2}\\:){5}([a-fA-F]|\\d){2})"};
    return std::regex_match(item.data(), pattern);
}

int main()
{
    std::cout << std::boolalpha << is_mac_address("2a:27:c7:b7:3d:17") << '\n';
}
