#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <regex>

namespace ip {
[[nodiscard]] bool is_private_a(const std::string_view& ip) {
  static const std::regex pattern{
      "10(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}"
  };
  return std::regex_match(ip.begin(), ip.end(), pattern);
}

[[nodiscard]] bool is_private_b(const std::string_view& ip) {
  static const std::regex pattern{
      "172(\\.(1[6-9]|2[0-9]|3[01]))(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"
  };
  return std::regex_match(ip.begin(), ip.end(), pattern);
}

[[nodiscard]] bool is_private_c(const std::string_view& ip) {
  static const std::regex pattern{
      "192\\.168(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"
  };
  return std::regex_match(ip.begin(), ip.end(), pattern);
}

[[nodiscard]] bool is_private(const std::string_view& ip) {
  return is_private_a(ip) || is_private_b(ip) || is_private_c(ip) ||
         ip == "127.0.0.1";
}

[[nodiscard]] bool is_ipv4(const std::string_view& ip) {
  static const std::regex pattern{
      std::format("{0}(\\.{0}){{3}}", "(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])")
  };
  return std::regex_match(ip.begin(), ip.end(), pattern);
}

[[nodiscard]] bool is_public(const std::string_view& ip) {
  const auto second_octect = ip.substr(4, 2);

  return !ip.starts_with("10") && !ip.starts_with("192.168.") &&
         !(ip.starts_with("172.") && ip[6] == '.' && second_octect >= "16" &&
           second_octect <= "31") &&
         ip != "127.0.0.1" && is_ipv4(ip);
}

[[nodiscard]] bool is_ipv6(const std::string_view& ip) {
  static const std::regex pattern{
      std::format("^{0}(:{0}){{7}}$", "[0-9|a-f|A-F]{1,4}")
  };
  return std::regex_match(ip.begin(), ip.end(), pattern);
}
} // namespace ip

TEST_CASE("is_private_a returns true for range [10.0.0.0, 10.255.255.255]") {
  REQUIRE(ip::is_private_a("10.0.0.0") == true);
  REQUIRE(ip::is_private_a("10.40.2.254") == true);
  REQUIRE(ip::is_private_a("10.255.255.255") == true);
  REQUIRE(ip::is_private_a("8.10.10.10") == false);
  REQUIRE(ip::is_private_a("7.6.5.4") == false);
}

TEST_CASE("is_private_b returns true for range [172.16.0.0, 172.31.255.255]") {
  REQUIRE(ip::is_private_b("172.16.0.0") == true);
  REQUIRE(ip::is_private_b("172.20.2.254") == true);
  REQUIRE(ip::is_private_b("172.31.255.255") == true);
  REQUIRE(ip::is_private_b("81.10.10.10") == false);
  REQUIRE(ip::is_private_b("172.61.5.4") == false);
}

TEST_CASE(
    "is_private_c returns true for range [192.168.0.0, 192.168.255.255]"
) {
  REQUIRE(ip::is_private_c("192.168.0.0") == true);
  REQUIRE(ip::is_private_c("192.168.1.254") == true);
  REQUIRE(ip::is_private_c("192.168.255.255") == true);
  REQUIRE(ip::is_private_c("192.167.1.54") == false);
  REQUIRE(ip::is_private_c("192.68.2.3") == false);
}

TEST_CASE("is_private_ip") {
  REQUIRE(ip::is_private("8.8.8.8") == false);
  REQUIRE(ip::is_private("1.1.1.1") == false);
  REQUIRE(ip::is_private("10.81.82.83") == true);
  REQUIRE(ip::is_private("172.17.2.14") == true);
  REQUIRE(ip::is_private("192.168.4.5") == true);
}

TEST_CASE("is_public_ip") {
  REQUIRE(ip::is_public("8.8.8.8") == true);
  REQUIRE(ip::is_public("81.82.83.84") == true);
  REQUIRE(ip::is_public("43.2.1.254") == true);
  REQUIRE(ip::is_public("10.2.1.92") == false);
  REQUIRE(ip::is_public("127.0.0.1") == false);
}

TEST_CASE("is_ipv4 returns true for range [0.0.0.0, 255.255.255.255]") {
  REQUIRE(ip::is_ipv4("7.2.44.80") == true);
  REQUIRE(ip::is_ipv4("222.50.3.6") == true);
  REQUIRE(ip::is_ipv4("41.23.21.54") == true);
  REQUIRE(ip::is_ipv4("310.62.11.9") == false);
  REQUIRE(ip::is_ipv4("2.28.35.258") == false);
}

TEST_CASE(
    "is_ipv6 returns true for range [0000:0000:0000:0000:0000:0000:0000:0000, "
    "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff]"
) {
  REQUIRE(ip::is_ipv6("0000:0000:0000:0000:0000:0000:0000:0000") == true);
  REQUIRE(ip::is_ipv6("c3:0:f2:bd:a3:f01:ff3:23") == true);
  REQUIRE(ip::is_ipv6("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff") == true);
  REQUIRE(ip::is_ipv6("af:0:33:g12:ff2:92:55:cb") == false);
  REQUIRE(ip::is_ipv6("22:d3:23:0:0:39:fc9:12:1") == false);
}

TEST_CASE("is_private_a", "[!benchmark]") {
  REQUIRE(ip::is_private_a("10.0.0.0") == true);
  REQUIRE(ip::is_private_a("10.255.255.255") == true);

  BENCHMARK("is_private_a(10.255.255.255)") {
    return ip::is_private_a("10.255.255.255");
  };
}

TEST_CASE("is_private_b", "[!benchmark]") {
  REQUIRE(ip::is_private_b("172.16.0.0") == true);
  REQUIRE(ip::is_private_b("172.20.2.254") == true);

  BENCHMARK("is_private_b(172.31.255.255)") {
    return ip::is_private_b("172.31.255.255");
  };
}

TEST_CASE("is_private_c", "[!benchmark]") {
  REQUIRE(ip::is_private_c("192.168.0.0") == true);
  REQUIRE(ip::is_private_c("192.168.1.254") == true);

  BENCHMARK("is_private_c(192.168.255.255)") {
    return ip::is_private_c("192.168.255.255");
  };
}

TEST_CASE("is_private", "[!benchmark]") {
  REQUIRE(ip::is_private("10.81.82.83") == true);
  REQUIRE(ip::is_private("172.17.2.14") == true);

  BENCHMARK("is_private(192.168.255.255)") {
    return ip::is_private("192.168.255.255");
  };
}

TEST_CASE("is_ipv4", "[!benchmark]") {
  REQUIRE(ip::is_ipv4("222.50.3.6") == true);
  REQUIRE(ip::is_ipv4("41.23.21.54") == true);

  BENCHMARK("is_ipv4(41.23.21.54)") {
    return ip::is_ipv4("41.23.21.54");
  };
}