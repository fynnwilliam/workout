#include <iostream>
#include <vector>

unsigned long grid_traveler_t(int m, int n)
{
    std::vector<std::vector<unsigned long>> v(m + 1, std::vector<unsigned long>(n + 1));
    v[1][1] = 1;
    
    for (std::size_t i{}; i < v.size(); ++i)
    {
        for (std::size_t j{}; j < v[i].size(); ++j)
        {
            if (i != m)
                v[i + 1][j] += v[i][j];
            
            if (j != n)
                v[i][j + 1] += v[i][j];
        }
    }
    
    return v[m][n];
}


int main()
{
    std::cout << grid_traveler_t(18, 18) << '\n';
}
