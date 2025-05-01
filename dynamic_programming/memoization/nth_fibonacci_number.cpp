#include <catch2/catch_test_macros.hpp>
#include <unordered_map>

unsigned long nth_fibonacci(int n) {
  static std::unordered_map<int, unsigned long> m;

  return m.count(n) ? m[n]
         : n < 1    ? 0
         : n == 1   ? 1
                    : m[n] = nth_fibonacci(n - 1) + nth_fibonacci(n - 2);
}

TEST_CASE("nth_fibonacci") {
  REQUIRE(nth_fibonacci(93) == 12'200'160'415'121'876'738zu);
}