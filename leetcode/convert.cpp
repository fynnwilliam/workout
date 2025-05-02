#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("convert") {
  REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
  REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
  REQUIRE(convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");
}

TEST_CASE("convert", "[!benchmark]") {
  REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
  REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
  REQUIRE(convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");

  std::string s(1'000'000, 'a');
  BENCHMARK("convert(std::string s(1'000'000, 'a'), 10)") {
    return convert(s, 10);
  };
}