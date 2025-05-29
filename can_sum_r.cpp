#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <vector>

bool factor_of(int target, int i) {
  return target % i == 0;
}

bool can_sum_r(int target, std::vector<int> const& v) {
  for (int elem : v) {
    if (factor_of(target, elem))
      return true;

    auto present = [&](int a) { return a == target - elem || a == target; };
    if (std::any_of(std::begin(v), std::end(v), present))
      return true;
  }

  return false;
}

TEST_CASE("can_sum_r") {
  REQUIRE(can_sum_r(7, {2, 3}) == false);
  REQUIRE(can_sum_r(7, {2, 4, 6}) == false);
  REQUIRE(can_sum_r(7, {5, 3, 4, 7}) == true);
}