#include "array.h"

int main()
{
    array<int> a{10};

    int i{};
    for ( auto& elem : a) elem = ++i;
    
    for ( auto const& elem : a) std::cout << elem << '\n';
}