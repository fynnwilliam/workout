#include <iostream>
#include <cassert>

#include "array.h"

int main()
{
    array a{3};
    std::cout << " setting a[0] = 10\n";
    a[0] = 10;
    std::cout << " a[0] is " << a[0] << '\n';
}