#include <iostream>
#include <string>

char first_recurring_char(std::string const& s)
{   
    for (std::size_t i{}; i < s.size() - 1; ++i)
    {
        if (auto pos = s.find_last_of(s[i]); pos > i && pos < s.size())
            return s[i];
    }
    
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