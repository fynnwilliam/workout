#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

const auto fib_fast = [](uint8_t n) {
  assert(n < 94);
  if (n == 0 || n > 93)
    return 0zu;

  size_t f1 = 1, f2 = 1, result = 1;
  while (n-- > 2) {
    result = f1 + f2;
    f1 = f2;
    f2 = result;
  }

  return result;
};

TEST_CASE("fib_fast") {
  REQUIRE(fib_fast(2) == 1zu);
  REQUIRE(fib_fast(39) == 63'245'986zu);
  REQUIRE(fib_fast(50) == 12'586'269'025zu);
  REQUIRE(fib_fast(71) == 308'061'521'170'129zu);
  REQUIRE(fib_fast(93) == 12'200'160'415'121'876'738zu);
}

TEST_CASE("fib_fast", "[!benchmark]") {
  BENCHMARK("fib_fast 71") { return fib_fast(93); };
}