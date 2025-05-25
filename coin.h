#pragma once
#include <algorithm>
#include <vector>

#include "point.h"

class coin {
private:
  int path_{};
  point location_;
  std::vector<coin> neighbours_;

public:
  coin() = delete;
  coin(point p) : location_{p} {}

  int path() const {
    return path_;
  }
  point const& location() const {
    return location_;
  }
  std::vector<coin> const& neighbours() const {
    return neighbours_;
  }

  void update_neighbours(std::vector<coin> coins) {
    point current_location{location_};

    for (auto const& c : coins) {
      coin b = closest_coin(current_location, coins);

      std::erase_if(coins, [&](auto const& c) { return c == b; });

      neighbours_.push_back(b);
      current_location.move_to(b.location());
    }
  }

  void update_path() {
    if (neighbours_.size() == 1) {
      path_ = 0;
    } else {
      for (std::size_t i{}; i < neighbours_.size() - 1; ++i) {
        path_ += neighbours_[i].location() - neighbours_[i + 1].location();
      }
    }
  }

  friend coin closest_coin(point c, std::vector<coin> coins) {
    coin closest_c{coins[0]};

    for (auto const& coin : coins) {
      if (c - coin.location() < c - closest_c.location())
        closest_c = coin;
    }

    return closest_c;
  }

  inline bool operator==(coin const& rhs) const {
    return path() == rhs.path() && location() == rhs.location() &&
           neighbours_ == rhs.neighbours_;
  }

  friend bool compare(auto const& a, auto const& b) {
    return a == b;
  }
};

inline point _closest_coin(point player, const std::vector<point>& coins) {
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

inline std::vector<coin>
_shortest_path(point player, std::vector<coin>& coins) {
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

inline std::vector<coin> coin_list(const std::vector<point>& coins) {
  std::vector<coin> c;

  for (auto const& coin : coins)
    c.push_back(coin);

  return c;
}