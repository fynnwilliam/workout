#include <algorithm>
#include <cassert>
#include <concepts>
#include <vector>

template <typename Container>
concept insertable = requires(Container c, Container::value_type v) {
  c.insert(std::begin(c), v);
  { std::begin(c) } -> std::forward_iterator;
};

template <insertable T, typename... U>
  requires(std::same_as<typename T::value_type, U> && ...)
void insertion_sort(T& container, U... args) {
  for (auto const& arg : {args...}) {
    const auto itr = std::ranges::upper_bound(container, arg);
    container.insert(itr, arg);
  }
}

int main() {
  std::vector<int> numbers{1, 3, 4, 6, 7, 8};

  insertion_sort(numbers, 2, 0, 9, 5);
  assert((numbers == std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}