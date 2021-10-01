#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <list>

std::list<std::list<std::string>>
all_construct(std::string s, std::vector<std::string> word_bank, std::unordered_map<std::string, std::list<std::list<std::string>>>&& m = {})
{
    if (m.count(s)) return m[s];
    if (s.empty()) return {{}};
    
    std::list<std::list<std::string>> result;
    
    for (auto& word : word_bank)
    {
        if (s.find(word) == 0)
        {
            auto suffix_list = all_construct(s.substr(word.length()), word_bank, std::move(m));
            
            for (auto& elem : suffix_list)
                elem.push_front(word);
            
            for (auto& elem : suffix_list)
                result.push_back(elem);
        }
    }

    return m[s] = result;
}

void display(std::list<std::list<std::string>>const& lists)
{
    for (auto& inner : lists)
    {
        for (auto& elem : inner)
            std::cout << elem << ' ';
        
        std::cout << '\n';
    }
    
    std::cout << '\n';
}

int main()
{
    display(all_construct("purple", {"purp", "p", "ur", "le", "purl"}));
    display(all_construct("abcdef", {"ab", "abc", "cd", "def", "abcd", "ef", "c"}));
    display(all_construct("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}));
    display(all_construct("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}));
}
