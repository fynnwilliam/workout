#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

template <typename T>
concept elem = requires(T x, typename T::value_type value)
              {
                  { x.begin() } -> std::forward_iterator;
                    x.insert(x.begin(), value);
              };

template <typename T>
    requires elem<T>
void insertion_sort(T& container, typename T::value_type value)
{
    auto itr{std::ranges::upper_bound(container, value)};
    container.insert(itr, value);
}

int main()
{
    std::vector<int>  numbers{1, 3, 4, 6, 7, 8, 10};

    insertion_sort(numbers, 2);
    insertion_sort(numbers, 0);
    insertion_sort(numbers, 9);
}