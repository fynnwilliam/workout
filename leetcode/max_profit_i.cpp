#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

int max_profit_i(const std::vector<int>& prices) {
  if (prices.size() < 2)
    return 0;

  int max_profit = 0;
  int max_bid = prices.back();
  for (size_t i = prices.size() - 2; i > 0; --i) {
    max_profit = std::max(max_bid - prices[i], max_profit);
    max_bid = std::max(max_bid, prices[i]);
  }

  return std::max(max_bid - prices[0], max_profit);
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