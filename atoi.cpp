#include <array>
#include <catch2/benchmark/catch_benchmark.hpp>
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

TEST_CASE("_atoi(-1353)") {
  std::string_view sv = "-1353";
  auto begin = sv.begin();
  auto end = sv.end();

  REQUIRE(_atoi(begin, end) == -1353);
}

TEST_CASE("_atoi(1'123'456'789)") {
  std::string_view sv = "1123456789";
  auto begin = sv.begin();
  auto end = sv.end();

  REQUIRE(_atoi(begin, end) == 1'123'456'789);
}

TEST_CASE("_atoi", "[!benchmark]") {
  std::string_view sv = "1123456789";
  auto begin = sv.begin();
  auto end = sv.end();

  REQUIRE(_atoi(begin, end) == 1'123'456'789);

  BENCHMARK("atoi(1'123'456'789)") { return _atoi(begin, end); };
}