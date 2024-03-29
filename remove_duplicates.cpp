#include <iterator>
#include <iostream>
#include <vector>

void print(std::vector<int> v)
{
    for (auto elem : v)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void copy_elem(auto i, auto const& j)
{
    for ( ; i < j - 1; ++i)
    {
        *i = *(i + 1);
    }
}

int main()
{
    std::vector<int> v{1, 2, 2, 3, 4, 4, 5, 6, 7, 8};
                   // {1, 2, 3, 4, 4, 5, 6, 7, 8, 8};
                   // {1, 2, 3, 4, 5, 6, 7, 8, 8, 8};
    print(v);
    
    int count{};
    for (auto i{begin(v)}; v.size() && i < end(v) - 1 - count; ++i)
    {
        if (*i == *(i + 1))
        {
            copy_elem(i + 1, end(v) - count++);
        }
    }
    
    v.erase(end(v) - count, end(v));
    
    print(v);

    std::cout << "number of duplicates found: " << count << '\n';
}