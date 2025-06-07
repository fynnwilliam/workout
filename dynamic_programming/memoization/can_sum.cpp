#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

bool can_sum(
    int target, std::vector<int> const& v, std::unordered_map<int, bool>& m
) {
  if (m.count(target))
    return m[target];
  if (!target)
    return true;
  if (target < 0)
    return false;

  for (int elem : v) {
    if (can_sum(target - elem, v, m)) {
      return m[target] = true;
    }
  }

  return m[target] = false;
}

TEST_CASE("can_sum") {
  std::unordered_map<int, bool> a, b, c, d, e, f, g;
  REQUIRE(can_sum(7, std::vector<int>{2, 3}, a) == true);
  REQUIRE(can_sum(7, std::vector<int>{5, 3, 4, 7}, b) == true);
  REQUIRE(can_sum(7, std::vector<int>{2, 4}, c) == false);
  REQUIRE(can_sum(19, std::vector<int>{12, 3, 5}, d) == true);
  REQUIRE(can_sum(41, std::vector<int>{7, 15}, e) == false);
  REQUIRE(can_sum(8, std::vector<int>{2, 3, 5}, f) == true);
  REQUIRE(can_sum(300, std::vector<int>{7, 14}, g) == false);
}