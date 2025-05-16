#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

void copy_elem(auto i, auto const& j) {
  for (; i < j - 1; ++i) {
    *i = *(i + 1);
  }
}

auto remove_duplicate(auto& v) {
  std::size_t count{};
  for (auto i{begin(v)}; v.size() && i < end(v) - 1 - count; ++i) {
    if (*i == *(i + 1)) {
      copy_elem(i + 1, end(v) - count++);
    }
  }

  v.erase(end(v) - count, end(v));
  return count;
}

TEST_CASE("remove_duplicate") {
  std::vector<int> v{1, 2, 2, 3, 4, 4, 5, 6, 7, 8};

  REQUIRE(remove_duplicate(v) == 2);
  REQUIRE(v == std::vector{1, 2, 3, 4, 5, 6, 7, 8});
}