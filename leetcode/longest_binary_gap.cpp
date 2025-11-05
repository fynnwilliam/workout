#include <bitset>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

int longest_binary_gap(int n) {
  const auto n_str = std::bitset<32>(n).to_string();

  auto first = n_str.find("10");
  auto last = n_str.find("01", first + 1);

  if (first == std::string::npos || last == std::string::npos)
    return 0;

  int longest_gap = static_cast<int>(last - first);
  while (first < last) {
    first = n_str.find("10", last + 1);
    last = n_str.find("01", first + 1);

    if (first == std::string::npos || last == std::string::npos)
      return longest_gap;

    if (int gap = static_cast<int>(last - first); gap > longest_gap)
      longest_gap = gap;
  }

  return longest_gap;
}

TEST_CASE("longest_binary_gap") {
  CHECK(longest_binary_gap(1) == 0);
  CHECK(longest_binary_gap(5) == 1);
  CHECK(longest_binary_gap(10) == 1);
  CHECK(longest_binary_gap(41) == 2);
  CHECK(longest_binary_gap(16'785'441) == 10);
}

TEST_CASE("longest_binary_gap", "[!benchmark]") {

  CHECK(longest_binary_gap(16'785'441) == 10);
  BENCHMARK("longest_binary_gap(16785441)") {
    return longest_binary_gap(16'785'441);
  };
}
