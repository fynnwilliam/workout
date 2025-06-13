#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

std::vector<int> best_sum(
    int target, std::vector<int> const& v,
    std::unordered_map<int, std::vector<int>> m = {}
) {
  if (m.count(target))
    return m[target];
  if (!target)
    return std::vector<int>{};
  if (target < 0)
    return std::vector{-1};

  std::vector<int> shortest_c{-1};

  for (const auto& elem : v) {
    auto current_c = best_sum(target - elem, v, std::move(m));
    if (current_c.empty() || current_c[0] != -1) {
      current_c.push_back(elem);
      if (current_c.size() < shortest_c.size() || shortest_c[0] == -1) {
        shortest_c = std::move(current_c);
      }
    }
  }

  return m[target] = shortest_c;
}

TEST_CASE("best_sum") {
  REQUIRE(best_sum(8, {1, 2, 4, 25}) == std::vector{4, 4});
  REQUIRE(best_sum(7, {5, 3, 4, 7}) == std::vector{7});
  REQUIRE(best_sum(8, {2, 3, 5}) == std::vector{5, 3});
  REQUIRE(best_sum(100, {1, 2, 5, 25}) == std::vector{25, 25, 25, 25});
}

TEST_CASE("best_sum", "[!benchmark]") {
  const std::vector v{1, 2, 5, 25};
  BENCHMARK("best_sum(100, v)") {
    return best_sum(100, v);
  };
}