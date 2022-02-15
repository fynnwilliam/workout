#include <iostream>
#include <string>

auto reverse_str(std::string s)
{
    if (s.empty()) return std::string{};

    return reverse_str(s.substr(1)) + s[0];
}

int main()
{
    std::cout << reverse_str("perception") << std::endl;
}