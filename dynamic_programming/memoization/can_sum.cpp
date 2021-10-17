#include <unordered_map>
#include <iostream>
#include <utility>
#include <vector>

bool can_sum(int target, std::vector<int> const& v, std::unordered_map<int, bool>&& m = {})
{
    if (m.count(target))  return m[target];
    if (!target)          return true;
    if (target < 0)       return false;
    
    for (int elem : v)
    {
        if (can_sum(target - elem, v, std::move(m)))
        {
            return m[target] = true;
        }
    }
   
    return m[target] = false;
}

int main()
{
    std::cout << std::boolalpha << can_sum(7,  std::vector<int>{2, 3})       << '\n'
                                << can_sum(7,  std::vector<int>{5, 3, 4, 7}) << '\n'
                                << can_sum(7,  std::vector<int>{2, 4})       << '\n'
                                << can_sum(19, std::vector<int>{12, 3, 5})   << '\n'
                                << can_sum(41, std::vector<int>{7, 15})      << std::endl;
}