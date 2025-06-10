#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

auto can_sum = [cache = std::vector<std::uint8_t>{}](
                   int target, const std::vector<int>& v
               ) mutable {
  const auto new_size = static_cast<std::size_t>(target + 1);
  const auto n = cache.size() > new_size ? new_size : cache.size();
  cache.resize(new_size, 2);
  std::fill_n(cache.data(), n, 2);

  return [&cache](this auto&& can_sum_, int t, const auto& v_) -> std::uint8_t {
    if (t < 0)
      return 0;
    if (t == 0)
      return 1;

    const auto& target_ = static_cast<std::size_t>(t);
    if (cache[target_] < 2)
      return cache[target_];

    for (const auto& elem : v_) {
      if (can_sum_(t - elem, v_) == 1) {
        return cache[target_] = 1;
      }
    }

    return cache[target_] = 0;
  }(target, v) == 1;
};

TEST_CASE("can_sum") {
  REQUIRE(can_sum(7, std::vector<int>{2, 3}) == true);
  REQUIRE(can_sum(7, std::vector<int>{5, 3, 4, 7}) == true);
  REQUIRE(can_sum(7, std::vector<int>{2, 4}) == false);
  REQUIRE(can_sum(19, std::vector<int>{12, 3, 5}) == true);
  REQUIRE(can_sum(41, std::vector<int>{7, 15}) == false);
  REQUIRE(can_sum(8, std::vector<int>{2, 3, 5}) == true);
  REQUIRE(can_sum(300, std::vector<int>{7, 14}) == false);
}

TEST_CASE("can_sum", "[!benchmark]") {
  std::vector v{7, 14};
  BENCHMARK("can_sum(300, v, m)") {
    return can_sum(300, v);
  };
}