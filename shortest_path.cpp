#include "coin.h"
#include <catch2/catch_test_macros.hpp>

std::vector<coin> shortest_path(point player, std::vector<coin> coins) {
  if (coins.empty())
    return coins;

  for (auto& coin : coins) {
    coin.update_neighbours(coins);
    coin.update_path();
  }

  auto min{coins[0]};
  int min_base_length{player - min.location()};
  for (auto const& coin : coins) {
    int base_length{player - coin.location()};
    if (base_length + coin.path() < min_base_length + min.path())
      min = coin;
  }

  return min.neighbours();
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