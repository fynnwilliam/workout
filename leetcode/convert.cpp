#include <catch2/catch_test_macros.hpp>

TEST_CASE("convert") {
  REQUIRE(convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
  REQUIRE(convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
  REQUIRE(convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");
}