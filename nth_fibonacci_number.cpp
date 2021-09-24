#include <iostream>
#include <unordered_map>

unsigned long nth_fibonacci(int n)
{
    static std::unordered_map<int, unsigned long> m;
    
    if (m.count(n)) return m[n];
    if (n <= 0)     return 0;
    if (n == 1)     return 1;

    m[n] = nth_fibonacci(n - 1) + nth_fibonacci(n - 2);
    
    return m[n];
}

int main()
{
    std::cout << nth_fibonacci(10'000) << std::endl;
}