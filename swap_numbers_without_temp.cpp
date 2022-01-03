#include <cassert>
#include <concepts>

template <typename T>
    requires std::integral<T> || std::floating_point<T>
void swap_without_temp(T& a, T& b)
{
    a += b;
    b = a - b;
    a -= b;
}

int main()
{
    char a{'a'};
    char b{'b'};
    
    swap_without_temp(a, b);
    assert(a == 'b' && b == 'a');
}