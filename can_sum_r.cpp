#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <vector>

bool factor_of(int target, int i) {
  return target % i == 0;
}

bool can_sum_r(int target, std::vector<int> const& v) {
  for (auto first = std::begin(v), last = std::end(v); first < last; ) {
    int elem = *first;
    if (factor_of(target, elem))
      return true;

    auto is_present = [=, b = target - elem](int a) {
      return a == b || a == target;
    };
    if (std::any_of(++first, last, is_present))
      return true;
  }

  return false;
}

TEST_CASE("can_sum_r") {
  REQUIRE(can_sum_r(7, {2, 3}) == false);
  REQUIRE(can_sum_r(7, {2, 4, 6}) == false);
  REQUIRE(can_sum_r(7, {5, 3, 4, 7}) == true);
}

TEST_CASE("can_sum_r", "[!benchmark]") {
  std::vector<int> v(1'000'000, 5);
  v.back() = 2;

  REQUIRE(can_sum_r(7, v) == true);

  BENCHMARK("can_sum_r(7, v)") {
    return can_sum_r(7, v);
  };
}