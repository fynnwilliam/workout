#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <regex>

[[nodiscard]] bool is_mac_address(std::string_view item) {
  static const std::regex pattern{
      "((([a-fA-F]|\\d){2}(\\:|\\-)){5}([a-fA-F]|\\d){2})"
  };
  return std::regex_match(item.data(), pattern);
}

TEST_CASE("is_mac_address") {
  REQUIRE(is_mac_address("2a:27:c7:b7:3d:17") == true);
  REQUIRE(is_mac_address("01-23-45-67-89-ab") == true);
  REQUIRE(is_mac_address("00-1A-2B-3C-4D-5E") == true);
  REQUIRE(is_mac_address("2a:27:c7:z7:3d:17") == false);
  REQUIRE(is_mac_address("2a:27a:c7:b7:3d:17") == false);
}

TEST_CASE("is_mac_address", "[!benchmark]") {
  BENCHMARK("is_mac_address(01-23-45-67-89-ab)") {
    return is_mac_address("01-23-45-67-89-ab");
  };
}