#include "coin.h"

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