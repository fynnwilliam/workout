#include <array>
#include <catch2/catch_test_macros.hpp>

int _atoi(const char* b, const char* e) {
  constexpr std::array<unsigned long, 10> pow10{
      1'000'000'000UL, 100'000'000UL, 10'000'000UL, 1'000'000UL, 100'000UL,
      10'000UL,        1'000UL,       100UL,        10UL,        1UL
  };

  int sign = 1;
  if (*b == '-') {
    sign = -1;
    ++b;
  }

  assert(b < e);
  int number = 0;
  auto i = sizeof(pow10) / sizeof(pow10[0]) - (e - b);
  for (; b != e; ++b) {
    const auto digit = unsigned(*b) - '0';
    assert(digit < 10);
    number += pow10[i++] * digit;
  }
  return number * sign;
}

TEST_CASE("_atoi") { REQUIRE(_atoi("-135d3") == -135); }