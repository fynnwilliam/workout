#include <unordered_map>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>

std::unique_ptr<std::vector<int>> how_sum(int target, std::vector<int> const& v, std::unordered_map<int, std::unique_ptr<std::vector<int>>>&& m = {})
{
    if (m.count(target)) return std::move(m[target]);
    if (!target) return std::unique_ptr<std::vector<int>> {new std::vector<int>{}};
    if (target < 0) return {{}};
    
    for (int elem : v)
    {
        if (auto result = how_sum(target - elem, v, std::move(m)); result)
        {
            result->push_back(elem);
            return std::move(m[target] = std::move(result));
        }
    }

    
    return std::move(m[target] = {{}});
}

int main()
{
    auto v{ how_sum(100, {3, 33, 13, 5, 8}) };
    
    if (!v)
    {
        std::cout << "could not sum up...\n";
        return 0;
    }
    
    for (int elem : *v)
        std::cout << elem << ' ';

    std::cout << std::endl;
}
