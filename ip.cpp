#include <catch2/catch_test_macros.hpp>
#include <string>
#include <regex>

bool private_a(std::string const& ip)
{
    std::regex pattern{"([1][0])(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){3}"};
    return std::regex_match(ip, pattern);
}

bool private_b(std::string const& ip)
{
    std::regex pattern{"([1][7][2])(\\.(1[6-9]|2[0-9]|3[01]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip, pattern);
}

bool private_c(std::string const& ip)
{
    std::regex pattern{"([1][9][2])(\\.([1][6][8]))(\\.([01]?[0-9][0-9]?|2[0-4][0-9]|25[0-5])){2}"};
    return std::regex_match(ip, pattern);
}

bool private_ip(std::string const& ip)
{
    return private_a(ip) || private_b(ip) || private_c(ip);
}

bool public_ip(std::string const& ip)
{
    return !private_ip(ip);
}

TEST_CASE("private_a returns true for range [10.0.0.0, 10.255.255.255]") {
  REQUIRE(private_a("10.0.0.0") == true);
  REQUIRE(private_a("10.40.2.254") == true);
  REQUIRE(private_a("10.255.255.255") == true);
  REQUIRE(private_a("8.10.10.10") == false);
  REQUIRE(private_a("7.6.5.4") == false);
}

TEST_CASE("private_b returns true for range [172.16.0.0, 172.31.255.255]") {
  REQUIRE(private_b("172.16.0.0") == true);
  REQUIRE(private_b("172.20.2.254") == true);
  REQUIRE(private_b("172.31.255.255") == true);
  REQUIRE(private_b("81.10.10.10") == false);
  REQUIRE(private_b("172.61.5.4") == false);
}

TEST_CASE("private_c returns true for range [192.168.0.0, 192.168.255.255]") {
  REQUIRE(private_c("192.168.0.0") == true);
  REQUIRE(private_c("192.168.1.254") == true);
  REQUIRE(private_c("192.168.255.255") == true);
  REQUIRE(private_c("192.167.1.54") == false);
  REQUIRE(private_c("192.68.2.3") == false);
}

TEST_CASE("private_ip") {
  REQUIRE(private_ip("8.8.8.8") == false);
}

TEST_CASE("public_ip") {
  REQUIRE(public_ip("8.8.8.8") == true);
}