#include "coin.h"
#include <cassert>

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

int main() {
  point a{0, 1};
  std::vector<point> coins{
      {1, 3},
      {2, 0},
      {0, 2},
      {4, 4},
      {0, 0}
  };

  assert((closest_coin(a, coins) == point{0, 2}));
}