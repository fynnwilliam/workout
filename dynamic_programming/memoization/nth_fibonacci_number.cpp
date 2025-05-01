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
  REQUIRE(nth_fibonacci(2) == 1zu);
  REQUIRE(nth_fibonacci(39) == 63'245'986zu);
  REQUIRE(nth_fibonacci(50) == 12'586'269'025zu);
  REQUIRE(nth_fibonacci(71) == 308'061'521'170'129zu);
  REQUIRE(nth_fibonacci(93) == 12'200'160'415'121'876'738zu);
}