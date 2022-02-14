#include <iostream>
#include <string>
#include <vector>

bool can_construct(std::string target, std::vector<std::string> word_bank)
{
    std::vector<bool> table(target.size() + 1, false);
    table[0] = true;
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (auto const& word : word_bank)
        {
            if (table[i] && target.substr(i).find(word) == 0)
                table[i + word.length()] = table[i];
        }
    }
    
    return table.back();
}

int main()
{
  std::cout << std::boolalpha
            << can_construct("performance", {"per", "orm", "f", "p", "ance"})
            << std::endl;
}
