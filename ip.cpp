#include <catch2/catch_test_macros.hpp>
#include <regex>

namespace ip {
bool is_private_a(const std::string_view& ip)
{
    static const std::regex pattern{"10(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}"};
    return std::regex_match(ip.data(), pattern);
}

bool is_private_b(const std::string_view& ip)
{
    static const std::regex pattern{"172(\\.(1[6-9]|2[0-9]|3[01]))(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip.data(), pattern);
}

bool is_private_c(const std::string_view& ip)
{
    static const std::regex pattern{"192\\.168(\\.(1?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip.data(), pattern);
}

bool is_private(const std::string_view& ip)
{
    return is_private_a(ip) || is_private_b(ip) || is_private_c(ip) || ip == "127.0.0.1";
}

bool is_public(const std::string_view& ip)
{
    return !is_private(ip.data());
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

TEST_CASE("is_private_c returns true for range [192.168.0.0, 192.168.255.255]") {
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