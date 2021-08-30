#include <iostream>
#include <cassert>

#include "array.h"

int main()
{
    try
    {
        array a{10};
        for (int i = 0; i < a.size(); ++i)
        {
            a[i] = (i + 1) * 10;
        }
        
        std::cout << " array elements: ";
        for (int i = 0; i < a.size(); ++i)
        {
            std::cout << a[i] << ' ';
        }
        std::cout << '\n';
        
        std::cout << " array size is " << a.size() << '\n';
        std::cout << " please enter an array index: ";
        int index{};
        std::cin >> index;
        
        std::cout << " the element at index " << index << " is " << a[index] << '\n';
    }
    
    catch(std::exception const& e) { std::cout << "\n *** error: " << e.what() << '\n'; }
}