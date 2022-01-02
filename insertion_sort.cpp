#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>

template <typename T>
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

    insertion_sort(numbers, 2, 0, 9);
    assert((numbers == std::vector{0, 1, 2, 3, 4, 6, 7, 8, 9, 10}));
}