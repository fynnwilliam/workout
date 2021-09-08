#include <iostream>
#include <string>

std::string reverse_str(std::string s)
{
    std::string reversed{s};

    std::size_t size{};
    while (s[size] != '\0') ++size;

    for (char const& c : s) reversed[--size] = c;
    
    return reversed;
}

int main()
{
    std::cout << reverse_str("how are you doing?") << std::endl;
}