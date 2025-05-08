#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

const auto fib_fast = [](uint8_t n) -> size_t {
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

constexpr auto nth_fibonacci = [](uint8_t n) -> size_t {
  constexpr double phi = 1.6'180'339'887'498'949'025;
  constexpr double psi = -0.6'180'339'887'498'949'025;
  constexpr double sqrt_five = 2.23'606'797'749'979;

  return static_cast<size_t>((std::pow(phi, n) - std::pow(psi, n)) / sqrt_five);
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

TEST_CASE("nth_fibonacci") {
  REQUIRE(nth_fibonacci(2) == 1zu);
  REQUIRE(nth_fibonacci(17) == 1'597);
  REQUIRE(nth_fibonacci(39) == 63'245'986zu);
  REQUIRE(nth_fibonacci(50) == 12'586'269'025zu);
  REQUIRE(nth_fibonacci(71) == 308'061'521'170'129zu);
}

TEST_CASE("nth_fibonacci", "[!benchmark]") {
  BENCHMARK("nth_fibonacci 71") { return nth_fibonacci(71); };
}