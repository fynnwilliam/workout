#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

char first_non_recurring_char(std::string const& s) {
  for (std::size_t i{1}; i < s.size(); ++i) {
    if (s.find_last_of(s[i]) == i && s[i] != s[i - 1])
      return s[i];
  }

  return ' ';
}

TEST_CASE("first_non_recurring_char") {
  using namespace std::string_literals;
  REQUIRE(first_non_recurring_char("character"s) == 'h');
  REQUIRE(first_non_recurring_char("recurring"s) == 'e');
  REQUIRE(first_non_recurring_char("maximised"s) == 'a');
  REQUIRE(first_non_recurring_char("applejack"s) == 'l');
}

TEST_CASE("first_non_recurring_char", "[!benchmark]") {
  std::string s(1'000'000, ' ');
  s.append("a");

  BENCHMARK("first_non_recurring_char(s)") {
    return first_non_recurring_char(s);
  };
}