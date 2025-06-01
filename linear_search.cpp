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
  auto first = std::cbegin(arr);
  auto last = std::cend(arr);

  REQUIRE(*linear_search(first, last, 3) == 3);
  REQUIRE(*linear_search(first, last, 4) == 4);
  REQUIRE(*linear_search(first, last, 9) == 9);
  REQUIRE(linear_search(first, last, 1) == last);
}

TEST_CASE("linear_search", "[!benchmark]") {
  int arr[1'000]{3, 4, 33, 9, 23, 99};
  arr[989] = 42;

  auto first = std::cbegin(arr);
  auto last = std::cend(arr);

  BENCHMARK("linear_search(f, l, 42)") {
    return linear_search(first, last, 42);
  };
}