#include <iostream>
#include <regex>

bool is_valid_email(std::string const& item)
{
    std::regex pattern{"(\\w+)(\\.|_)?(\\w+)\\@(\\w+)(\\.(\\w+))+"};
    return std::regex_match(item, pattern);
}

int main()
{
    std::cout << std::boolalpha << is_valid_email("example@email.com") << std::endl;
}