#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

std::uint8_t
can_sum(int target, const std::vector<int>& v, std::vector<std::uint8_t>& m) {
  if (target < 0)
    return 0;
  if (target == 0)
    return 1;
  if (target >= m.size())
    m.resize(target + 1, 2);
  else if (m[target] < 2)
    return m[target];

  for (const auto& elem : v) {
    if (can_sum(target - elem, v, m) == 1) {
      return m[target] = 1;
    }
  }

  return m[target] = 0;
}

TEST_CASE("can_sum") {
  std::vector<std::uint8_t> a, b, c, d, e, f, g;
  REQUIRE(can_sum(7, std::vector<int>{2, 3}, a) == 1);
  REQUIRE(can_sum(7, std::vector<int>{5, 3, 4, 7}, b) == 1);
  REQUIRE(can_sum(7, std::vector<int>{2, 4}, c) == 0);
  REQUIRE(can_sum(19, std::vector<int>{12, 3, 5}, d) == 1);
  REQUIRE(can_sum(41, std::vector<int>{7, 15}, e) == 0);
  REQUIRE(can_sum(8, std::vector<int>{2, 3, 5}, f) == 1);
  REQUIRE(can_sum(300, std::vector<int>{7, 14}, g) == 0);
}

TEST_CASE("can_sum", "[!benchmark]") {
  std::vector<std::uint8_t> m;
  std::vector v{7, 14};
  BENCHMARK("can_sum(300, v, m)") {
    return can_sum(300, v, m);
  };
}