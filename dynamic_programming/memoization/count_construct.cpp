#include <unordered_map>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

int count_construct(std::string s, std::vector<std::string> word_bank, std::unordered_map<std::string, int>&& m = {})
{
    if (m.count(s)) return m[s];
    if (s.empty())  return 1;
    
    int total_count{};
    
    for (auto& word : word_bank)
    {
        if (s.find(word) == 0)
        {
            total_count += count_construct(s.substr(word.length()), word_bank, std::move(m));
        }
    }
    
    return m[s] = total_count;
}


int main()
{
    std::vector<std::string> v{"a", "p", "ent", "enter", "ot", "o", "t"};

    std::cout << std::boolalpha << count_construct("enterapotentpot", v) << std::endl;
}