#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> best_sum(int target, std::vector<int> v)
{
    std::vector<std::vector<int>> table(target + 1);
    table[0] = {0};
    
    for (std::size_t i{}; i < table.size(); ++i)
    {
       for (int num : v)
       {
           if (table[i].size() && i + num < table.size())
           {
               auto temp = table[i];
               temp.push_back(num);
               
               if (table[i + num].empty())
                   table[i + num] = temp;
               
               if (temp.size() < table[i + num].size())
                   table[i + num] = temp;
           }
       }
   }
   
   std::erase(table.back(), 0);
   return table.back();
}

void print(std::vector<int>& v)
{
    for (int i : v)
        std::cout << i << ' ';
        
    std::cout << '\n';
}

int main()
{
    auto v = best_sum(8, {2, 4, 3, 7});
    
    print(v);
}
