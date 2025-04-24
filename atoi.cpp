#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

int _atoi(std::string_view s) {
  auto b = s.begin();
  auto e = s.end();

  int sign{1};
  if (*b == '-') {
    sign = -1;
    ++b;
  }

  int number{};
  for (; b < e ; ++b) {
    auto digit = unsigned(*b) - '0';
    assert(digit < 10);
    number = number * 10 + digit;
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