#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

void copy_elem(auto i, auto const& j) {
  for (; i < j; ++i) {
    *i = *(i + 1);
  }
}

auto remove_duplicate(auto& v) {
  std::size_t count{};
  auto last = std::end(v) - 1;
  
  for (auto i = std::begin(v); i < last; ++i) {
    if (auto m = i + 1; *i == *m) {
      copy_elem(m, last--);
      ++count;
    }
  }

  v.erase(++last, std::end(v));
  return count;
}

TEST_CASE("remove_duplicate") {
  std::vector<int> v{1, 2, 2, 3, 4, 4, 5, 6, 7, 8};

  REQUIRE(remove_duplicate(v) == 2);
  REQUIRE(v == std::vector{1, 2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("remove_duplicate", "[!benchmark]") {
  std::vector v{1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 9, 9, 10, 12, 12, 14, 15, 16};
  BENCHMARK("remove_duplicate(v)") {
    return remove_duplicate(v);
  };
}