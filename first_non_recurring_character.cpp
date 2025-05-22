#include <catch2/catch_test_macros.hpp>
#include <string>

char first_non_recurring_char(std::string const& s) {
  for (std::size_t i{}; i < s.size(); ++i) {
    if (s.find_last_of(s[i]) == i)
      return s[i];
  }

  return ' ';
}

std::string declare(char const& c) {
  return c == ' ' ? "none found" : std::string{c};
}

TEST_CASE("first_non_recurring_char") {
  using namespace std::string_literals;
  REQUIRE(first_non_recurring_char("character"s) == 'h');
}