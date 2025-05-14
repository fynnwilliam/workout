#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

constexpr int set_bits(int n) { // Brian Kernighan's approach
  int count{};
  for (; n; count++)
    n &= n - 1;

  return count;
}

constexpr int _set_bits(int n) { // other approach
  int count{};

  while (n) {
    count += n & 1;
    n >>= 1;
  }

  return count;
}

TEST_CASE("set_bits") {
  REQUIRE(set_bits(128) == 1);
}

TEST_CASE("_set_bits") {
  REQUIRE(_set_bits(128) == 1);
}

TEST_CASE("set_bits", "[!benchmark]") {
  BENCHMARK("set_bits(128)") {
    return set_bits(128);
  };
}

TEST_CASE("_set_bits", "[!benchmark]") {
  BENCHMARK("_set_bits(128)") {
    return _set_bits(128);
  };
}