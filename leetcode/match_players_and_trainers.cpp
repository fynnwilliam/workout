#include <algorithm>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

int match_players_and_trainers(
    std::vector<int>& players, std::vector<int>& trainers
) {
  std::ranges::sort(players);
  std::ranges::sort(trainers);

  auto p_first = cbegin(players);
  auto p_end = cend(players);
  auto t_first = cbegin(trainers);
  auto t_end = cend(trainers);
  int matches = 0;
  while (p_first < p_end && t_first < t_end) {
    if (*p_first <= *t_first) {
      ++p_first;
      ++t_first;
      ++matches;
    } else
      ++t_first;
  }

  return matches;
}

TEST_CASE("match_players_and_trainers") {
  std::vector players{4, 7, 9};
  std::vector trainers{8, 2, 5, 8};
  REQUIRE(match_players_and_trainers(players, trainers) == 2);
}

TEST_CASE("match_players_and_trainers", "[!benchmark]") {
  std::vector players{4, 7, 9, 9, 2, 4, 10, 32, 9, 14};
  std::vector trainers{8, 2, 5, 8, 3, 4, 13, 29, 22, 7};

  BENCHMARK("match_players_and_trainers(players, trainers)") {
    return match_players_and_trainers(players, trainers);
  };
}