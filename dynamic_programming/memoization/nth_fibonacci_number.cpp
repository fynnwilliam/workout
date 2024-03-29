#include <cassert>
#include <iostream>
#include <unordered_map>

unsigned long nth_fibonacci(int n)
{
    static std::unordered_map<int, unsigned long> m;
    
    return m.count(n) ? m[n] :
           n <  1     ? 0    :
           n == 1     ? 1    :
           m[n] = nth_fibonacci(n - 1) + nth_fibonacci(n - 2);
}

int main()
{
    std::cout << nth_fibonacci(10'000) << std::endl;
    
    assert(nth_fibonacci(9'000) + nth_fibonacci(9'001) == nth_fibonacci(9'002));
}