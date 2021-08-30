#include <iostream>
#include <cassert>

#include "array.h"

int main()
{
    array a{10};
    for (int i = 0; i < a.size(); ++i)
    {
        a[i] = (i + 1) * 10;
    }
        
    std::cout << " array elements: " << a << '\n';
}