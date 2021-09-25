#include <unordered_map>
#include <iostream>
#include <cassert>
#include <string>

unsigned long grid_traveler(int m, int n)
{
    std::string key{std::to_string(m) + ',' + std::to_string(n)};
    static std::unordered_map<std::string, unsigned long> memo;
    
    if (memo.count(key))   return memo[key];
    if (!m || !n) 	      return 0;
    if (m == 1 && n == 1) return 1;
    
    memo[key] = grid_traveler(m - 1, n) + grid_traveler(m, n - 1);
    
    return memo[key];
}

int main()
{
    std::cout << grid_traveler(21, 91) << '\n';
    
    assert(grid_traveler(1,1) == 1);
    assert(grid_traveler(2,3) == 3);
    assert(grid_traveler(3,3) == 6);
    assert(grid_traveler(18,18) == 2333606220);
    assert(grid_traveler(10, 11) > grid_traveler(91, 2));
}