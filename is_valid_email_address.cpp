#include <catch2/catch_test_macros.hpp>
#include <regex>

bool is_valid_email(std::string_view item) {
  static const std::regex pattern{"(\\w+)(\\.|_)?(\\w+)\\@(\\w+)(\\.(\\w+))+"};
  return std::regex_match(item.data(), pattern);
}

TEST_CASE("is_valid_email") {
  REQUIRE(is_valid_email("example@email.com") == true);
  REQUIRE(is_valid_email("firstname.lastname@domain.com") == true);
  REQUIRE(is_valid_email("firstname_lastname@domain.com") == true);

  REQUIRE_FALSE(is_valid_email("example_email.com"));
  REQUIRE_FALSE(is_valid_email("example@email"));
}