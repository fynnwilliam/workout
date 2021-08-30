#include <iostream>

#include "array.h"

int main()
{
    array a{3};
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    
    array b = a;
    
    std::cout << " a = " << a << '\n';
    std::cout << " b = " << b << '\n';
    
    b[1] = 100;
    std::cout << "\n b[1] = 100; \n\n";
        
    std::cout << " a = " << a << '\n';
    std::cout << " b = " << b << '\n';
    
    array c{};
    array d = c;
    std::cout << ' ' << c << ' ' << d << '\n';
}