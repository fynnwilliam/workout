#include <iostream>

void hanoi(unsigned size, unsigned a, unsigned b, unsigned c)
{
    if (size)
    {
        hanoi(size - 1, a, c, b);
        std::cout << a << " -> " << c << '\n';
        hanoi(size - 1, b, a, c);
    }
}

int main()
{
    hanoi(10, 1, 2, 3);
}