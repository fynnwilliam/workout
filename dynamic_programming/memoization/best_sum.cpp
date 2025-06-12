#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

std::unique_ptr<std::vector<int>> best_sum(
    int target, std::vector<int> const& v,
    std::unordered_map<int, std::vector<int>> m = {}
) {
  if (m.count(target))
    return std::make_unique<std::vector<int>>(m[target]);
  if (!target)
    return std::make_unique<std::vector<int>>();
  if (target < 0)
    return nullptr;

  std::unique_ptr<std::vector<int>> shortest_c{};

  for (int elem : v) {
    if (auto current_c = best_sum(target - elem, v, std::move(m)); current_c) {
      current_c->push_back(elem);
      if (!shortest_c || current_c->size() < shortest_c->size()) {
        shortest_c = std::move(current_c);
      }
    }
  }

  if (shortest_c)
    m[target] = *shortest_c;
  return shortest_c;
}

TEST_CASE("best_sum") {
  REQUIRE(*best_sum(8, {1, 2, 4, 25}) == std::vector{4, 4});
  REQUIRE(*best_sum(7, {5, 3, 4, 7}) == std::vector{7});
  REQUIRE(*best_sum(8, {2, 3, 5}) == std::vector{5, 3});
  REQUIRE(*best_sum(100, {1, 2, 5, 25}) == std::vector{25, 25, 25, 25});
}