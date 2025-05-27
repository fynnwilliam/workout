#pragma once
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

    auto size = coins.size() + 1;
    while (--size) {
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
      const auto max_index = neighbours_.size() - 1;
      for (std::size_t i{}; i < max_index; ++i) {
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

  inline bool operator==(coin const&) const = default;
};