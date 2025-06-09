#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

bool can_sum(
    int target, const std::vector<int>& v, std::vector<std::uint8_t>& m
) {
  if (target < 0)
    return false;
  if (target == 0)
    return true;

  const auto& target_ = static_cast<std::size_t>(target);
  if (target_ >= m.size())
    m.resize(target_ + 1, 2);
  else if (m[target_] < 2)
    return m[target_] == 1;

  for (const auto& elem : v) {
    if (can_sum(target - elem, v, m)) {
      m[target_] = 1;
      return true;
    }
  }

  m[target_] = 0;
  return false;
}

TEST_CASE("can_sum") {
  std::vector<std::uint8_t> a, b, c, d, e, f, g;
  REQUIRE(can_sum(7, std::vector<int>{2, 3}, a) == true);
  REQUIRE(can_sum(7, std::vector<int>{5, 3, 4, 7}, b) == true);
  REQUIRE(can_sum(7, std::vector<int>{2, 4}, c) == false);
  REQUIRE(can_sum(19, std::vector<int>{12, 3, 5}, d) == true);
  REQUIRE(can_sum(41, std::vector<int>{7, 15}, e) == false);
  REQUIRE(can_sum(8, std::vector<int>{2, 3, 5}, f) == true);
  REQUIRE(can_sum(300, std::vector<int>{7, 14}, g) == false);
}

TEST_CASE("can_sum", "[!benchmark]") {
  std::vector<std::uint8_t> m;
  std::vector v{7, 14};
  BENCHMARK("can_sum(300, v, m)") {
    return can_sum(300, v, m);
  };
}