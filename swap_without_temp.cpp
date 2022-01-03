#include <cassert>
#include <concepts>
#include <string>

template <typename T>
    requires std::integral<T> || std::floating_point<T>
void swap_without_temp(T& a, T& b)
{
    a += b;
    b = a - b;
    a -= b;
}

template <typename T>
void swap_s(T& a, T& b)
{
    a.append(b);
    b = a.substr(0, a.size() - b.size());
    a = a.substr(b.size());
}

int main()
{
    char a{'a'};
    char b{'b'};
    
    swap_without_temp(a, b);
    assert(a == 'b' && b == 'a');
    
    std::string s1{"world"};
    std::string s2{"hello"};
}