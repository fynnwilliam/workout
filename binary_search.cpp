#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

template <typename T>
bool binary_search(const T* l, const T* h, const T& value) {
  while (l < h) {
    auto mid = l + ((h - l) / 2);

    if (*mid == value)
      return true;
    else if (*mid < value)
      l = ++mid;
    else
      h = --mid;
  }

  return value == *l;
}

TEST_CASE("binary_search") {
  using namespace std::string_literals;

  std::vector v{"cat"s, "cow"s, "dog"s, "rabbit"s, "sheep"s};
  const auto l = v.data();
  const auto h = l + v.size();

  REQUIRE(binary_search(l, h, "cat"s) == true);
  REQUIRE(binary_search(l, h, "cow"s) == true);
  REQUIRE(binary_search(l, h, "dog"s) == true);
  REQUIRE(binary_search(l, h, "rabbit"s) == true);
  REQUIRE(binary_search(l, h, "sheep"s) == true);
  REQUIRE(binary_search(l, h, "unknown"s) == false);
}

TEST_CASE("binary_search", "[!benchmark]") {
  using namespace std::string_literals;
  std::vector v{"cat"s, "cow"s, "dog"s, "rabbit"s, "sheep"s};

  const auto l = v.data();
  const auto h = l + v.size();

  BENCHMARK("binary_search(unknown, v_ptr, size)") {
    return binary_search(l, h, "unknown"s);
  };
}