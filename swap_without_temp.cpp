#include <cassert>
#include <concepts>
#include <string>

template <typename T>
    requires std::integral<T> || std::floating_point<T>
void swap_n(T& a, T& b)
{
    a += b;
    b = a - b;
    a -= b;
}

void swap_s(std::string& a, std::string& b)
{
    a.append(b);
    b = a.substr(0, a.size() - b.size());
    a = a.substr(b.size());
}

template <typename T>
void swap_without_temp(T& a, T& b)
{
    if constexpr (std::same_as<T, std::string>)
        return swap_s(a, b);
    else
        swap_n(a, b);
}

int main()
{
    char a{'a'};
    char b{'b'};
    
    swap_without_temp(a, b);
    assert(a == 'b' && b == 'a');
    
    std::string s1{"world"};
    std::string s2{"hello"};
    
    swap_without_temp(s1, s2);
    assert(s1 == "hello" && s2 == "world");
}