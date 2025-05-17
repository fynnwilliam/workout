#include <algorithm>
#include <catch2/catch_test_macros.hpp>
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

TEST_CASE("insertion_sort") {
  std::vector<int> numbers{1, 3, 4, 6, 7, 8};
  insertion_sort(numbers, 2, 0, 9, 5);
  REQUIRE((numbers == std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}