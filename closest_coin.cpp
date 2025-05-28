#include "coin.h"
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

coin closest_coin(point player, const std::vector<coin>& coins) {
  auto closest_c = std::data(coins);
  auto minimum_distance = player - closest_c->location();
  auto first = closest_c + 1;
  auto last = closest_c + coins.size();

  for (; first < last; ++first) {
    const auto& location = first->location();
    if (auto distance = player - location; distance < minimum_distance) {
      closest_c = first;
      minimum_distance = distance;
    }
  }

  return !closest_c || closest_c == last ? coin{point{0, 0}} : * closest_c;
}

TEST_CASE("closest_coin") {
  std::vector<coin> coins{
      point{1, 3},
      point{2, 0},
      point{0, 2},
      point{4, 4},
      point{0, 0}
  };

  REQUIRE(::closest_coin(point{0, 1}, coins).location() == point{0, 2});
}

TEST_CASE("closest_coin", "[!benchmark]") {
  std::vector<coin> coins{
      point{1, 3},
      point{2, 0},
      point{0, 2},
      point{4, 4},
      point{0, 0}
  };

  BENCHMARK("::closest_coin(point coins)") {
    return ::closest_coin(point{0, 1}, coins);
  };
}