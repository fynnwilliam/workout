#include "coin.h"
#include <catch2/catch_test_macros.hpp>

coin closest_coin(point player, const std::vector<coin>& coins) {
  coin closest_c{coins[0]};

  auto minimum_distance = player - closest_c.location();
  for (auto const& coin : coins) {
    if (auto distance = player - coin.location(); distance < minimum_distance) {
      closest_c = coin;
      minimum_distance = distance;
    }
  }

  return closest_c;
}

TEST_CASE("closest_coin") {
  std::vector<coin> coins{
      point{1, 3},
      point{2, 0},
      point{0, 2},
      point{4, 4},
      point{0, 0}
  };

  REQUIRE(::closest_coin(point{0, 1}, coins) == point{0, 2});
}