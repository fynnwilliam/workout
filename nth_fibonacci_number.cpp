#include <iostream>

int nth_fibonacci(int n)
{
    return n <= 0 ? 0 :
           n == 1 ? 1 : nth_fibonacci(n - 1) + nth_fibonacci(n - 2);
}

int main()
{
    std::cout << nth_fibonacci(40) << std::endl;
}