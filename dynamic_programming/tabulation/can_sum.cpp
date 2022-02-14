#include <array>
#include <iostream>
#include <vector>

bool can_sum(int const target, std::vector<int> v)
{
    std::vector<bool> table(target + 1, false);
    table[0] = true;
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (std::size_t j{}; j < v.size(); ++j)
        {
            if (table[i] && i + v[j] < table.size())
                table[i + v[j]] = table[i];
        }
    }

    return table[target];
}

int main()
{
    std::cout << std::boolalpha << can_sum(7, {5, 3, 4}) << '\n';
} 
