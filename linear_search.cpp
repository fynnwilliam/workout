#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

template <typename T>
int linear_search(T elem, T const* v, int const& size) noexcept {
  for (int i = 0; i < size; ++i) {
    if (v[i] == elem)
      return i;
  }

  return -1;
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