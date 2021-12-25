#include <iostream>
#include <numeric>
#include <ctime>
#include <array>

std::size_t sum_of_n(std::size_t n)
{
    return n * (n + 1) / 2;
}

int missing_number(auto const& numbers)
{
    std::size_t expected_sum = sum_of_n(numbers.size());
    std::size_t current_sum  = std::accumulate(numbers.begin(), numbers.end(), 0);
    
    return expected_sum - current_sum;
}

int main()
{
    std::array<int, 100> numbers;
    std::iota(numbers.begin(), numbers.end(), 1);
    
    std::srand(std::time(nullptr));
    numbers[std::rand() % 100] = 0;
    
    std::cout << missing_number(numbers) << std::endl;
}