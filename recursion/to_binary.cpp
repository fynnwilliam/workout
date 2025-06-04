#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

std::string to_binary(int d) {
  return !d ? std::string{'0'} : to_binary(d / 2) + std::to_string(d % 2);
}

TEST_CASE("to_binary") {
  using namespace std::string_literals;
  REQUIRE(to_binary(233) == "011101001"s);
  REQUIRE(to_binary(100) == "01100100"s);
  REQUIRE(to_binary(121) == "01111001"s);
}

TEST_CASE("to_binary", "[!benchmark]") {
  BENCHMARK("to_binary(128)") {
    return to_binary(128);
  };
}