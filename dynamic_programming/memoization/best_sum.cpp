#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using numbers = std::vector<std::uint32_t>;

numbers
best_sum(std::uint32_t target, numbers const& v, std::vector<numbers>& cache) {
  if (!target)
    return numbers{};

  if (target >= cache.size())
    cache.resize(target + 1, numbers{0u});
  else if (cache[target][0] != 0u)
    return cache[target];

  numbers shortest_c{0u};

  for (const auto& elem : v) {
    if (elem <= target) {
      auto current_c = best_sum(target - elem, v, cache);
      current_c.emplace_back(elem);
      if (current_c.size() < shortest_c.size() || shortest_c[0] == 0u) {
        shortest_c = std::move(current_c);
      }
    }
  }

  return cache[target] = shortest_c;
}

TEST_CASE("best_sum") {
  std::vector<numbers> a, b, c, d;
  REQUIRE(best_sum(8, {1, 2, 4, 25}, a) == std::vector{4u, 4u});
  REQUIRE(best_sum(7, {5, 3, 4, 7}, b) == std::vector{7u});
  REQUIRE(best_sum(8, {2, 3, 5}, c) == std::vector{5u, 3u});
  REQUIRE(best_sum(100, {1, 2, 5, 25}, d) == std::vector{25u, 25u, 25u, 25u});
}

TEST_CASE("best_sum", "[!benchmark]") {
  const numbers v{1, 2, 5, 25};
  std::vector<numbers> m;
  BENCHMARK("best_sum(100, v, m)") {
    return best_sum(100, v, m);
  };
}