#include "array.h"

int main()
{
    array<int> a{3};
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    
    array<int> b = a;
    
    std::cout << " a = " << a << '\n';
    std::cout << " b = " << b << '\n';
    
    b[1] = 100;
    std::cout << "\n b[1] = 100; \n\n";
        
    std::cout << " a = " << a << '\n';
    std::cout << " b = " << b << '\n';
    
    array<double> c{};
    array<double> d = c;
    std::cout << ' ' << c << ' ' << d << '\n';
}