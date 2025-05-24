#include <catch2/catch_test_macros.hpp>
#include <string>

char first_recurring_char(std::string const& s) {
  for (std::size_t i{}; i < s.size() - 1; ++i) {
    if (s.find_last_of(s[i]) != i)
      return s[i];
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