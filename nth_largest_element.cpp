#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <numeric>

auto extract_unique(const auto& v) {
  std::vector<int> unique_numbers;

  unique_numbers.reserve(v.size());
  std::ranges::copy(v, std::back_inserter(unique_numbers));
  std::ranges::sort(unique_numbers);
  std::ranges::unique(unique_numbers);

  return unique_numbers;
}

int nth_largest_element(auto const& v, std::size_t index) {
  auto s = extract_unique(v);
  return s.size() >= index ? s[--index] : -1;
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