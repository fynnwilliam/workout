#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <set>

std::set<int> extract_unique(std::vector<int> const& v) {
  std::set<int> s;
  for (auto elem : v) {
    s.insert(elem);
  }

  return s;
}

int nth_largest_element(auto const& v, std::size_t index) {
  std::set<int> s{extract_unique(v)};

  std::size_t count{1};
  for (auto i{begin(s)}; i != end(s); ++i, ++count) {
    if (count == index)
      return *i;
  }

  return -1;
}

TEST_CASE("nth_largest_element") {
  std::vector<int> v{1, 3, 2, 17, 18, 8, 19, 22, 2, 10, 11, 11, 133};
  REQUIRE(nth_largest_element(v, 9) == 19);
}

TEST_CASE("nth_largest_element", "[!benchmark]") {
  std::vector<int> numbers(1'000'000);
  std::ranges::iota(numbers, 1);

  BENCHMARK("nth_largest_element(numbers)") {
    return nth_largest_element(numbers, 1'000);
  };
}