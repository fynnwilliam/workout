#include <iostream>
#include <string_view>

bool palindrome(std::string_view sv)
{
    return sv.size() < 2             ? true
           : sv.front() == sv.back() ? palindrome(sv.substr(1, sv.size() - 2))
                                     : false;
}

int main()
{
    std::cout << std::boolalpha << palindrome("kayak") << std::endl;
}