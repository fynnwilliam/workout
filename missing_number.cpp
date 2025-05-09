#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>

std::size_t sum_of_n(std::size_t n) {
  return n * (n + 1) / 2;
}

size_t missing_number(auto const& numbers) {
  size_t expected_sum = sum_of_n(numbers.size());
  size_t current_sum = std::accumulate(numbers.begin(), numbers.end(), 0zu);

  return expected_sum - current_sum;
}

int main() {
  std::array<int, 100> numbers;
  std::iota(numbers.begin(), numbers.end(), 1);

  std::mt19937 gen{std::random_device{}()};
  std::uniform_int_distribution<size_t> distributor(0, 100);

  numbers[distributor(gen)] = 0;

  std::cout << missing_number(numbers) << std::endl;
}