#include <iostream>
#include <string>
#include <vector>

int count_construct(std::string s, std::vector<std::string> word_bank)
{
    std::vector<int> table(s.size() + 1, 0);
    table[0] = 1;
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (auto& word : word_bank)
        {
            if (table[i] && s.substr(i).find(word) == 0)
                table[i + word.size()] += table[i];
        }
    }

    return table.back();
}

int main()
{
    std::cout << std::boolalpha
              << count_construct("purple", {"purp", "p", "ur", "le", "purpl"})
              << '\n';
}
