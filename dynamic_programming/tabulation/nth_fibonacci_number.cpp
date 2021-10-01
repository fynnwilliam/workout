#include <iostream>
#include <vector>

unsigned long fib_tabulation(unsigned n)
{
    if (!n) return 0;

    std::vector<unsigned long> v(n + 1, 0);
    v[1] = 1;

    for (std::size_t i{}; i < v.size() - 1; ++i)
    {
        v[i + 1] += v[i];

        if (i < v.size() - 2)
            v[i + 2] += v[i];
    }
    
    return v.back();
}
        
int main()
{
    std::cout << fib_tabulation(0) << '\n';
}
