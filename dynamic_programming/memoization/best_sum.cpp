#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

std::vector<int> best_sum(
    int target, std::vector<int> const& v, std::vector<std::vector<int>>& cache
) {
  if (!target)
    return std::vector<int>{};

  const auto& target_ = static_cast<std::size_t>(target);
  if (target_ >= cache.size())
    cache.resize(target_ + 1, std::vector{-1});
  else if (cache[target_][0] != -1)
    return cache[target_];

  std::vector<int> shortest_c{-1};

  for (const auto& elem : v) {
    if (elem <= target) {
      auto current_c = best_sum(target - elem, v, cache);
      current_c.emplace_back(elem);
      if (current_c.size() < shortest_c.size() || shortest_c[0] == -1) {
        shortest_c = std::move(current_c);
      }
    }
  }

  return cache[target_] = shortest_c;
}

TEST_CASE("best_sum") {
  std::vector<std::vector<int>> a, b, c, d;
  REQUIRE(best_sum(8, {1, 2, 4, 25}, a) == std::vector{4, 4});
  REQUIRE(best_sum(7, {5, 3, 4, 7}, b) == std::vector{7});
  REQUIRE(best_sum(8, {2, 3, 5}, c) == std::vector{5, 3});
  REQUIRE(best_sum(100, {1, 2, 5, 25}, d) == std::vector{25, 25, 25, 25});
}

TEST_CASE("best_sum", "[!benchmark]") {
  const std::vector v{1, 2, 5, 25};
  std::vector<std::vector<int>> m;
  BENCHMARK("best_sum(100, v, m)") {
    return best_sum(100, v, m);
  };
}