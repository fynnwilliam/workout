#include <iostream>
#include <numeric>
#include <ctime>
#include <array>

unsigned sum_of_n(std::size_t n)
{
    return n * (n + 1) / 2;
}

int missing_number(auto const& numbers)
{
    unsigned expected_sum = sum_of_n(numbers.size());
    unsigned current_sum  = std::accumulate(numbers.begin(), numbers.end(), 0);
    
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