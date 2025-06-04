#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <string>

std::string to_binary(int d) {
  return !d ? std::string{'0'} : to_binary(d / 2) + std::to_string(d % 2);
}

TEST_CASE("to_binary") {
  using namespace std::string_literals;
  REQUIRE(to_binary(233) == "011101001"s);
}