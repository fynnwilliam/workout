#include <iostream>
#include <string>

char first_non_recurring_char(std::string const& s)
{
    for (std::size_t i{}; i < s.size(); ++i)
    {
        if (s.find_last_of(s[i]) == i)
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
    char c =  first_non_recurring_char(std::string{"character"});
    
    std::cout << declare(c) << std::endl;
}