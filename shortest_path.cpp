#include "coin.h"
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

std::vector<coin> shortest_path(point player, std::vector<coin> coins) {
  if (coins.empty())
    return coins;

  for (auto& coin : coins) {
    coin.update_neighbours(coins);
    coin.update_path();
  }

  auto min = std::cbegin(coins);
  int min_length = player - min->location() + min->path();
  for (auto first = min + 1, last = std::cend(coins); first < last; ++first) {
    int length = player - first->location();
    if ((length += first->path()) < min_length) {
      min = first;
      min_length = length;
    }
  }

  return min->neighbours();
}

TEST_CASE("shortest_path") {
  const auto coins = shortest_path(
      point{
          0, 1
  },
      std::vector<coin>{
          point{1, 3}, point{2, 0}, point{0, 2}, point{4, 4}, point{0, 0}
      }
  );

  REQUIRE(coins[0].location() == point{2, 0});
  REQUIRE(coins[1].location() == point{0, 0});
  REQUIRE(coins[2].location() == point{0, 2});
  REQUIRE(coins[3].location() == point{1, 3});
  REQUIRE(coins[4].location() == point{4, 4});
}

TEST_CASE("shortest_path", "[!benchmark]") {
  std::vector<coin> coins{
      point{1, 3},
      point{2, 0},
      point{0, 2},
      point{4, 4},
      point{0, 0}
  };

  BENCHMARK("shortest_path(p, coins)") {
    return shortest_path(point{0, 1}, coins);
  };
}