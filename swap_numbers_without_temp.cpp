#include <iostream>

template <typename T>
void swap_without_temp(T& a, T& b)
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