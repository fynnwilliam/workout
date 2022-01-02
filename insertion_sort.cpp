#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>
#include <iostream>

template <typename T>
    requires requires(T x, typename T::value_type value)
        {{ x.begin() } -> std::forward_iterator; x.insert(x.begin(), value);}
void _insertion_sort(T& container, typename T::value_type value)
{
    auto itr{std::ranges::upper_bound(container, value)};
    container.insert(itr, value);
}

template <typename T, typename... U>
    requires requires(T x, typename T::value_type value)
        {{ x.begin() } -> std::forward_iterator; x.insert(x.begin(), value);}
    && (std::same_as<typename T::value_type, U> && ...)
void insertion_sort(T& container, U... values)
{
    for (auto const& value : {values...})
        _insertion_sort(container, value);
}

int main()
{
    std::vector<int>  numbers{1, 3, 4, 6, 7, 8, 10};

    insertion_sort(numbers, 2);
    insertion_sort(numbers, 0);
    insertion_sort(numbers, 9);
    
    assert((numbers == std::vector{0, 1, 2, 3, 4, 6, 7, 8, 9, 10}));
    
    std::vector<int> v{1, 3, 9, 10, 11};
    insertion_sort(v, 2, 10, 20, 4, 11, 7, 5, 100);
    
    for (int elem : v)
        std::cout << elem << ' ';
    std::cout << '\n';
}