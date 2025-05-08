#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <unordered_map>

auto nth_fibonacci_map = [cache = std::unordered_map<uint8_t, size_t>{
                              {0, 0zu},
                              {1, 1zu},
                              {2, 1zu}
}](this auto&& fib, uint8_t n) -> size_t {
  auto& r = cache[n];
  if (r > 0uz)
    return r;
  return r = fib(n - 1) + fib(n - 2);
};

auto nth_fibonacci_vector = [cache = std::vector<size_t>{0zu, 1zu, 1zu}](
                                this auto&& fib, uint8_t n
                            ) -> size_t {
  if (n < cache.size()) {
    if (cache[n] > 0zu || n == 0)
      return cache[n];
  } else {
    cache.resize(n + 1, 0zu);
  }

  return cache[n] = fib(n - 1) + fib(n - 2);
};

auto nth_fibonacci_array = [cache = std::array<size_t, 256zu>{0zu, 1zu, 1zu}](
                               this auto&& fib, uint8_t n
                           ) -> size_t {
  assert(n < 94);
  auto& r = cache[n];
  if (r > 0zu || n == 0)
    return r;
  return r = fib(n - 1) + fib(n - 2);
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

TEST_CASE("nth_fibonacci_map", "[!benchmark]") {
  BENCHMARK("nth_fibonacci_map 71") {
    return nth_fibonacci_map(71);
  };
}

TEST_CASE("nth_fibonacci_vector", "[!benchmark]") {
  BENCHMARK("nth_fibonacci_vector 71") {
    return nth_fibonacci_vector(71);
  };
}

TEST_CASE("nth_fibonacci_array", "[!benchmark]") {
  BENCHMARK("nth_fibonacci_array 71") {
    return nth_fibonacci_array(71);
  };
}