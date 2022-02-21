#include <algorithm>
#include <iostream>
#include <string>

auto anagram(std::string a, std::string b)
{
    if (a.size() != b.size()) return false;

    std::sort(begin(a), end(a));
    std::sort(begin(b), end(b));
    
    return a == b;
}

int main()
{
    std::cout << std::boolalpha << anagram("abcdef", "fedcba") << std::endl;
}