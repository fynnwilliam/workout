#include <iostream>
#include <string_view>

bool is_palindrome(std::string_view sv)
{
    return sv.size() < 2             ? true
           : sv.front() == sv.back() ? is_palindrome(sv.substr(1, sv.size() - 2))
                                     : false;
}

int main()
{
    std::cout << std::boolalpha << is_palindrome("kayak") << std::endl;
}