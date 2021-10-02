#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> all_construct(std::string s, std::vector<std::string> word_bank)
{
    std::vector<std::vector<std::vector<std::string>>> table(s.size() + 1);
    table[0] = {{}};
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (auto& word : word_bank)
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

void print(auto& v)
{
    for (auto& outter : v)
    {
        for (auto& inner : outter)
        {
            std::cout << inner << ' ';
        }
        
        std::cout << '\n';
    }
}

int main()
{
    auto v = all_construct("hefaefef", {"he", "is", "fe", "faef", "ef", "f", "fae"});
    
    print(v);
}
