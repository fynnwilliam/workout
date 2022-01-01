#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

template <typename T>
    requires requires(T x, typename T::value_type value)
    {
        { x.begin() } -> std::forward_iterator;
          x.insert(x.begin(), value);
    }
void insertion_sort(T& container, typename T::value_type value)
{
    auto itr{std::ranges::upper_bound(container, value)};
    container.insert(itr, value);
}

template <typename T>
void print(T const& container)
{
    for (typename T::value_type elem : container)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector<int>  numbers{1, 3, 4, 6, 7, 8, 10};
    std::vector<char> characters{'a', 'c', 'd', 'f', 'h'};

    insertion_sort(numbers, 2);
    insertion_sort(numbers, 0);
    insertion_sort(numbers, 9);
    
    insertion_sort(characters, 'b');
    insertion_sort(characters, 'e');
    insertion_sort(characters, 'i');
    
    print(numbers);
    print(characters);
}