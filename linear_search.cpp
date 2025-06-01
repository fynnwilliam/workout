#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

template <std::forward_iterator Itr, typename Element>
Itr linear_search(Itr first, Itr last, const Element& e) noexcept {
  --first;
  while (++first < last) {
    if (*first == e)
      return first;
  }

  return first;
}

TEST_CASE("linear_search") {
  int arr[]{3, 4, 33, 9, 23, 99};
  const int size = sizeof arr / sizeof arr[0];

  REQUIRE(linear_search(3, arr, size) == 0);
  REQUIRE(linear_search(4, arr, size) == 1);
  REQUIRE(linear_search(9, arr, size) == 3);
  REQUIRE(linear_search(1, arr, size) == -1);
}

TEST_CASE("linear_search", "[!benchmark]") {
  int arr[1'000]{3, 4, 33, 9, 23, 99};
  arr[989] = 42;
  const int size = sizeof arr / sizeof arr[0];

  BENCHMARK("linear_search(42, arr, size)") {
    return linear_search(42, arr, size);
  };
}