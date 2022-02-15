#include <iostream>
#include <string>

std::string reverse_str(std::string s)
{
    return s.empty() ? std::string{} : reverse_str(s.substr(1)) + s[0];
}

int main()
{
    std::cout << reverse_str("perception") << std::endl;
}