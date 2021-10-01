#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> how_sum(int target, std::vector<int> v)
{
    std::vector<std::vector<int>> table(target + 1);
    table[0] = {0};

    for (std::size_t i{}; i < table.size(); ++i)
    {
        for (int num : v)
        {
            if (table[i].size() && i + num < table.size())
            {
                table[i + num] = table[i];
                table[i + num].push_back(num);
            }
        }
    }
    
    std::erase(table.back(), 0);
    return table.back();
}


void print(std::vector<int>& v)
{
    for (int elem : v)
        std::cout << elem << ' ';
        
    std::cout << '\n';
}

int main()
{
    auto v = how_sum(7, {5, 3, 4});
    
    print(v);
}
