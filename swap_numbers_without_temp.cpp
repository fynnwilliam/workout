#include <iostream>

void swap_without_temp(int& a, int& b)
{
    a += b;
    b = a - b;
    a -= b;
}

int main()
{
    int a{};
    int b{3};
    
    swap_without_temp(a, b);
    std::cout << "a: " << a << '\n' 
              << "b: " << b << '\n';
}