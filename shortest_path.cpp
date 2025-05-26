#include "coin.h"
#include <catch2/catch_test_macros.hpp>

std::vector<coin> _shortest_path(point player, std::vector<coin>& coins) {
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

TEST_CASE("_shortest_path") {
  point a{0, 1};
  std::vector<coin> coins{
      point{1, 3},
      point{2, 0},
      point{0, 2},
      point{4, 4},
      point{0, 0}
  };

  REQUIRE(
      (_shortest_path(a, coins) ==
       std::vector<coin>{
           point{0, 1},
           point{2, 0},
           point{0, 0},
           point{0, 2},
           point{1, 3},
           point{4, 4}
  })
  );
}