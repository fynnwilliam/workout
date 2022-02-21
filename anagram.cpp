#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

auto anagram(std::string a, std::string b)
{
    if (a.size() != b.size()) return false;

    std::sort(begin(a), end(a));
    std::sort(begin(b), end(b));
    
    return a == b;
}

auto anagram_(std::string a, std::string b)
{
    if (a.size() != b.size()) return false;

    std::unordered_map<char, std::size_t> map_a;
    auto map_b = map_a;

    for (auto const& c : a) ++map_a[c];
    for (auto const& c : b) ++map_b[c];

    for (auto const& [key, value] : map_a)
        if (map_b[key] != value) return false;
    
    return true;
}

int main()
{
    std::cout << std::boolalpha << anagram ("abcdef", "fedcba") << std::endl;
    std::cout << std::boolalpha << anagram_("abcdef", "fedcba") << std::endl;
}