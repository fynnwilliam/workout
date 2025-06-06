#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

[[nodiscard]] auto anagram(std::string a, std::string b) {
  if (a.size() != b.size())
    return false;

  std::ranges::transform(a, a.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
  std::ranges::transform(b, b.begin(), [](unsigned char c) {
    return std::tolower(c);
  });

  std::ranges::sort(a);
  std::ranges::sort(b);

  return a == b;
}

[[nodiscard]] auto anagram_(std::string_view a, std::string_view b) {
  const auto size = a.size();
  if (size != b.size())
    return false;

  std::array<size_t, 26> letters_from_a{};
  std::array<size_t, 26> letters_from_b{};

  for (size_t i = 0zu; i < size; ++i) {
    ++letters_from_a[static_cast<size_t>(std::tolower((uint8_t(a[i]))) - 'a')];
    ++letters_from_b[static_cast<size_t>(std::tolower((uint8_t(b[i]))) - 'a')];
  }

  return letters_from_a == letters_from_b;
}

TEST_CASE("anagram") {
  REQUIRE(anagram("abcdef", "fedcba") == true);
  REQUIRE(anagram("Listen", "Silent") == true);
  REQUIRE(anagram("Earth", "Heart") == true);
  REQUIRE(anagram("Secure", "Rescue") == true);
  REQUIRE(
      anagram("hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone") ==
      true
  );
}

TEST_CASE("anagram_") {
  REQUIRE(anagram_("abcdef", "fedcba") == true);
  REQUIRE(anagram_("Listen", "Silent") == true);
  REQUIRE(anagram_("Earth", "Heart") == true);
  REQUIRE(anagram_("Secure", "Rescue") == true);
  REQUIRE(
      anagram_("hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone") ==
      true
  );
}

TEST_CASE("anagram", "[!benchmark]") {
  REQUIRE(anagram("Secure", "Rescue") == true);

  BENCHMARK("anagram(hydroxydeoxycorticosterones)") {
    return anagram(
        "hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone"
    );
  };
}

TEST_CASE("anagram_", "[!benchmark]") {
  REQUIRE(anagram_("Secure", "Rescue") == true);

  BENCHMARK("anagram_(hydroxydeoxycorticosterones)") {
    return anagram_(
        "hydroxydeoxycorticosterones", "hydroxydesoxycorticosterone"
    );
  };
}