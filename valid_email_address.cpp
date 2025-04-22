#include <iostream>
#include <regex>

bool is_valid_email(std::string_view item)
{
    static const std::regex pattern{"(\\w+)(\\.|_)?(\\w+)\\@(\\w+)(\\.(\\w+))+"};
    return std::regex_match(item.data(), pattern);
}

int main()
{
    std::cout << std::boolalpha << is_valid_email("example@email.com") << std::endl;
}