#include <catch2/catch_test_macros.hpp>

int _atoi(std::string_view s) {
  int index{};
  int sign{1};

  if (s[index] == '-') {
    sign = -1;
    ++index;
  }

  int res{};
  for (; s[index] != '\0'; ++index) {
    if (s[index] < '0' || s[index] > '9')
      break;

    res = res * 10 + s[index] - '0';
  }

  return res * sign;
}

TEST_CASE("_atoi") { REQUIRE(_atoi("-135d3") == -135); }