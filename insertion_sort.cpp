#include <algorithm>
#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& v, int value)
{
    auto itr{std::ranges::upper_bound(v, value)};
    v.insert(itr, value);
}

int main()
{
    std::vector<int> numbers{1, 3, 4, 6, 7, 8, 10};
    insertion_sort(numbers, 2);
    insertion_sort(numbers, 9);
    insertion_sort(numbers, 5);
    insertion_sort(numbers, 4);
    
    for (int elem : numbers)
        std::cout << elem << ' ';
        
    std::cout << std::endl;
}