#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <cassert>

bool factor_of(int target, int i)
{
    return target % i == 0;
}

bool can_sum_r(int target, std::vector<int> const& v)
{
    for (int elem : v)
    {
        if (factor_of(target, elem))
            return true;

        auto present = [&](int a) { return a == target - elem || a == target; };
        if (std::any_of(std::begin(v), std::end(v), present))
            return true;
    }
    
    return false;
}

int main()
{
    std::cout << std::boolalpha << can_sum_r(7, {2, 3}) << std::endl;
    
    assert(can_sum_r(7, {5, 3, 4, 7}) == true);
    assert(can_sum_r(7, {2, 4, 6,})   == false);
}