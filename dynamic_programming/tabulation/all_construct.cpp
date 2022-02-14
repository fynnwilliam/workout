#include <iostream>
#include <vector>
#include <string>

auto all_construct(std::string const& s, std::vector<std::string> const& word_bank)
{
    std::vector<std::vector<std::vector<std::string>>> table(s.size() + 1);
    table[0] = {{}};
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (auto const& word : word_bank)
        {
            if(table[i].size() && s.substr(i).find(word) == 0)
            {
                auto temp = table[i];
                for (auto& elem : temp)
                {
                    elem.push_back(word);
                    table[i + word.size()].push_back(elem);
                }
            }
         }
    }         
    
    return table.back();
}

void print(auto const& v)
{
    for (auto const& outter : v)
    {
        for (auto const& inner : outter)
            std::cout << inner << ' ';
        std::cout << '\n';
    }
}

int main()
{
    auto v = all_construct("hefaefef", {"he", "is", "fe", "faef", "ef", "f", "fae"});
    
    print(v);
}
