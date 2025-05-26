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

void shortest_path(point a, const std::vector<point>& coins) {
  auto coins_{coin_list(coins)};

  for (auto const& coin : _shortest_path(a, coins_)) {
    std::cout << a << " -> " << coin.location() << '\n';
    a.move_to(coin.location());
  }
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
  shortest_path(a, coins);
}