#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

[[nodiscard]] int _atoi(std::string_view s) {
  auto b = s.begin();
  auto e = s.end();

  int sign{1};
  if (*b == '-') {
    sign = -1;
    ++b;
  }

  int number{};
  for (; b < e; ++b) {
    auto digit = unsigned(*b) - '0';
    assert(digit < 10);
    number = number * 10 + digit;
  }

  return number * sign;
}

TEST_CASE("_atoi") {
  REQUIRE(_atoi("-1353") == -1353);
  REQUIRE(_atoi("1123456789") == 1'123'456'789);
}

TEST_CASE("_atoi", "[!benchmark]") {
  REQUIRE(_atoi("-1353") == -1353);
  REQUIRE(_atoi("1123456789") == 1'123'456'789);

  BENCHMARK("_atoi(1'123'456'789)") { return _atoi("1123456789"); };
}