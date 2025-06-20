#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

using numbers = std::vector<std::uint32_t>;

auto best_sum = [cache = std::vector<numbers>{{}}](
                    std::uint32_t target, const numbers& v
                ) mutable {
  const auto new_size = static_cast<std::size_t>(target + 1);
  const auto n = std::min(cache.size(), new_size);
  cache.resize(new_size, {0u});
  std::fill_n(cache.data() + 1, n - 1, numbers{0u});

  return [&cache](
             this auto&& best_sum_, std::uint32_t target_, numbers const& v_
         ) {
    if (target_ == 0u || cache[target_][0] != 0u)
      return cache[target_];

    numbers shortest_c{0u};

    for (const auto& elem : v_) {
      if (elem <= target_) {
        auto current_c = best_sum_(target_ - elem, v_);
        current_c.emplace_back(elem);
        if (current_c.size() < shortest_c.size() || shortest_c[0] == 0u) {
          shortest_c = std::move(current_c);
        }
      }
    }

    return cache[target_] = shortest_c;
  }(target, v);
};

TEST_CASE("best_sum") {
  REQUIRE(best_sum(8, {1, 2, 4, 25}) == std::vector{4u, 4u});
  REQUIRE(best_sum(7, {5, 3, 4, 7}) == std::vector{7u});
  REQUIRE(best_sum(8, {2, 3, 5}) == std::vector{5u, 3u});
  REQUIRE(best_sum(100, {1, 2, 5, 25}) == std::vector{25u, 25u, 25u, 25u});
}

TEST_CASE("best_sum", "[!benchmark]") {
  const numbers v{1, 2, 5, 25};
  BENCHMARK("best_sum(100, v)") {
    return best_sum(100, v);
  };
}