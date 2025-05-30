#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <random>

std::size_t sum_of_n(std::size_t n) {
  return n * (n + 1) / 2;
}

size_t missing_number(auto const& numbers) {
  size_t expected_sum = sum_of_n(numbers.size());
  size_t current_sum = std::accumulate(numbers.begin(), numbers.end(), 0zu);
  return expected_sum - current_sum;
}

namespace {
const size_t size = 100;
std::array<int, size> numbers;
std::mt19937 gen{std::random_device{}()};
std::uniform_int_distribution<size_t> distributor(0, size - 1);
} // namespace

TEST_CASE("missing_number") {
  SECTION("missing number should be equal to index + 1") {
    std::iota(numbers.begin(), numbers.end(), 1);
    auto index = distributor(gen);
    numbers[index] = 0;
    REQUIRE(missing_number(numbers) == index + 1);
  }

  SECTION("missing number should be equal to index + 1") {
    std::iota(numbers.begin(), numbers.end(), 1);
    auto index = distributor(gen);
    numbers[index] = 0;
    REQUIRE(missing_number(numbers) == index + 1);
  }
}

TEST_CASE("missing_number", "[!benchmark]") {
  std::iota(numbers.begin(), numbers.end(), 1);
  numbers[distributor(gen)] = 0;

  BENCHMARK("missing_number(numbers)") {
    return missing_number(numbers);
  };
}