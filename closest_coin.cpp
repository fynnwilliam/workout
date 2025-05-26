#include "coin.h"
#include <catch2/catch_test_macros.hpp>

point closest_coin(point player, const std::vector<point>& coins) {
  point closest_c{coins[0]};

  auto minimum_distance = player - closest_c;
  for (auto const& coin : coins) {
    if (auto distance = player - coin; distance < minimum_distance) {
      closest_c = coin;
      minimum_distance = distance;
    }
  }

  return closest_c;
}

TEST_CASE("closest_coin") {
  std::vector<point> coins{
      {1, 3},
      {2, 0},
      {0, 2},
      {4, 4},
      {0, 0}
  };

  REQUIRE(closest_coin(point{0, 1}, coins) == point{0, 2});
}