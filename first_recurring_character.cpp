#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

char first_recurring_char(std::string const& s) {
  for (auto index = 0uz, max_index = s.size() - 1; index < max_index; ++index) {
    if (s.find_last_of(s[index]) != index)
      return s[index];
  }

  return ' ';
}

TEST_CASE("first_recurring_char") {
  using namespace std::string_literals;
  REQUIRE(first_recurring_char("character"s) == 'c');
  REQUIRE(first_recurring_char("recurring"s) == 'r');
  REQUIRE(first_recurring_char("maximised"s) == 'm');
  REQUIRE(first_recurring_char("applejack"s) == 'a');
}

TEST_CASE("first_recurring_char", "[!benchmark]") {
  std::string s{"characters"};
  s.append(1'000'000, ' ');

  BENCHMARK("first_recurring_char(s)") {
    return first_recurring_char(s);
  };
}