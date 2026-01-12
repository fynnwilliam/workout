#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

int max_profit_i(const std::vector<int>& prices) {
  int max_profit = 0;
  const auto size = prices.size();

  for (size_t i = 0, i_size = size - 1; i < i_size; ++i) {
    const int& price = prices[i];
    int sell = price;
    for (size_t j = i + 1; j < size; ++j) {
      if (int p = prices[j]; p > sell)
        sell = p;
    }

    const int profit = sell - price;
    if (profit > max_profit)
      max_profit = profit;
  }

  return max_profit;
}

TEST_CASE("max_profit") {
  REQUIRE(max_profit_i({7, 1, 5, 3, 6, 4}) == 5);
  REQUIRE(max_profit_i({7, 6, 4, 3, 1}) == 0);
}

TEST_CASE("max_profit_i", "[!benchmark]") {
  std::vector prices(67'000, 0);
  BENCHMARK("max_profit_i") {
    return max_profit_i(prices);
  };
}