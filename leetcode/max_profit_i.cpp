#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

int max_profit_i(const std::vector<int>& prices) {
  const auto size = prices.size();

  if (size < 2) return 0;

  std::vector<int> bids(size, 0);
  for (size_t i = size - 2; i > 0; --i) {
    bids[i] = std::max(bids[i + 1], prices[i + 1]);
  }

  bids[0] = std::max(bids[1], prices[1]);

  int max_profit = 0;
  for (size_t i = 0, i_size = size - 1; i < i_size; ++i) {
    max_profit = std::max(bids[i] - prices[i], max_profit);
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