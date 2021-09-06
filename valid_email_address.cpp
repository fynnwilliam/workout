#include <iostream>
#include <regex>

bool valid_email(std::string const& item)
{
    std::regex pattern{"(\\w+)(\\.|_)?(\\w+)@(\\w+)(\\.(\\w+))+"};
    return std::regex_match(item, pattern);
}

int main()
{
    std::cout << std::boolalpha << valid_email("example@email.com") << std::endl;
}