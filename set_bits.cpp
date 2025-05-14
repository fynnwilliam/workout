#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

constexpr std::uint8_t set_bits(std::uint64_t n) { // Brian Kernighan's approach
  std::uint8_t count{};
  for (; n; count++)
    n &= n - 1;

  return count;
}

constexpr std::uint8_t _set_bits(std::uint64_t n) { // other approach
  std::uint8_t count{};

  while (n) {
    count += n & 1;
    n >>= 1;
  }

  return count;
}

TEST_CASE("set_bits") {
  REQUIRE(set_bits(0) == 0);
  REQUIRE(set_bits(128) == 1);
  REQUIRE(set_bits(UINT64_MAX) == 64);
}

TEST_CASE("_set_bits") {
  REQUIRE(_set_bits(0) == 0);
  REQUIRE(_set_bits(128) == 1);
  REQUIRE(_set_bits(UINT64_MAX) == 64);
}

TEST_CASE("set_bits", "[!benchmark]") {
  BENCHMARK("set_bits(128)") {
    return set_bits(UINT64_MAX);
  };
}

TEST_CASE("_set_bits", "[!benchmark]") {
  BENCHMARK("_set_bits(128)") {
    return _set_bits(UINT64_MAX);
  };
}