#include <iostream>
#include <cassert>

#include "array.h"

int main()
{
    std::cout << " creating an empty array.\n";
    array a{};
    std::cout << " a.size() is " << a.size() << '\n';
    assert(a.empty());
    
    std::cout << " -----------------------------------------\n";
    
    std::cout << " creating an array containing 10 elements.\n";
    array b{10};
    std::cout << " b.size() is " << b.size() << '\n';
    assert(!b.empty());
}