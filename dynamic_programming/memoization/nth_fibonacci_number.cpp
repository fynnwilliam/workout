#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <unordered_map>

auto nth_fibonacci_map = [cache = std::unordered_map<uint8_t, size_t>{
                              {0u, 0zu},
                              {1u, 1zu},
                              {2u, 1zu}
}](this auto&& fib, uint8_t n) -> size_t {
  auto& r = cache[n];
  if (r > 0uz)
    return r;
  return r = fib(n - 1u) + fib(n - 2u);
};

auto nth_fibonacci_vector = [cache = std::vector<size_t>{0zu, 1zu, 1zu}](
                                this auto&& fib, uint8_t n
                            ) -> size_t {
  if (n < cache.size()) {
    if (cache[n] > 0u || n == 0u)
      return cache[n];
  } else {
    cache.resize(n + 1, 0u);
  }

  return cache[n] = fib(n - 1) + fib(n - 2);
};

auto nth_fibonacci_array = [cache = std::array<size_t, 94zu>{1zu, 1zu, 1zu}](
                               this auto&& fib, uint8_t n
                           ) -> size_t {
  assert(n < 94u);
  auto& r = cache[n];
  if (r > 0zu || n == 0u)
    return r;
  return r = fib(n - 1u) + fib(n - 2u);
};

constexpr auto nth_fibonacci = [](uint8_t n) -> size_t {
  constexpr double phi = 1.6'180'339'887'498'949'025;
  constexpr double psi = -0.6'180'339'887'498'949'025;
  constexpr double sqrt_five = 2.23'606'797'749'979;

  return (std::pow(phi, n) - std::pow(psi, n)) / sqrt_five;
};

TEST_CASE("nth_fibonacci_map") {
  REQUIRE(nth_fibonacci_map(2) == 1zu);
  REQUIRE(nth_fibonacci_map(39) == 63'245'986zu);
  REQUIRE(nth_fibonacci_map(50) == 12'586'269'025zu);
  REQUIRE(nth_fibonacci_map(71) == 308'061'521'170'129zu);
  REQUIRE(nth_fibonacci_map(93) == 12'200'160'415'121'876'738zu);
}

TEST_CASE("nth_fibonacci_vector") {
  REQUIRE(nth_fibonacci_vector(2) == 1zu);
  REQUIRE(nth_fibonacci_vector(39) == 63'245'986zu);
  REQUIRE(nth_fibonacci_vector(50) == 12'586'269'025zu);
  REQUIRE(nth_fibonacci_vector(71) == 308'061'521'170'129zu);
  REQUIRE(nth_fibonacci_vector(93) == 12'200'160'415'121'876'738zu);
}

TEST_CASE("nth_fibonacci_array") {
  REQUIRE(nth_fibonacci_array(2) == 1zu);
  REQUIRE(nth_fibonacci_array(39) == 63'245'986zu);
  REQUIRE(nth_fibonacci_array(50) == 12'586'269'025zu);
  REQUIRE(nth_fibonacci_array(71) == 308'061'521'170'129zu);
  REQUIRE(nth_fibonacci_array(93) == 12'200'160'415'121'876'738zu);
}