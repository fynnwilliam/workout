#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

auto can_sum = [m = std::vector<std::uint8_t>{}](
                   int target, const std::vector<int>& v
               ) mutable {
  m.resize(static_cast<std::size_t>(target), 2);
  return [&m](this auto&& can_sum_, int t, const auto& v_) -> std::uint8_t {
    if (t < 0)
      return 0;
    if (t == 0)
      return 1;

    const auto& target_ = static_cast<std::size_t>(t);
    if (m[target_] < 2)
      return m[target_];

    for (const auto& elem : v_) {
      if (can_sum_(t - elem, v_) == 1) {
        return m[target_] = 1;
      }
    }

    return m[target_] = 0;
  }(target, v) == 1;
};

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