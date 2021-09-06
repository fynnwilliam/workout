#include <unordered_map>
#include <iostream>
#include <string>

char first_recurring_char(std::string const& s)
{
    std::unordered_map<char, int> m;
    
    for (char const& c : s)
        ++m[c];
    
    for (char const& c : s)
        if (m[c] > 1) return c;
    
    return ' ';
}

std::string declare(char const& c)
{
    return c == ' ' ? "none found" : std::string{c};
}

int main()
{
    char c = first_recurring_char(std::string{"character"});
    
    std::cout << declare(c) << std::endl;
}