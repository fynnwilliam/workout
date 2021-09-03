#include <iostream>
#include <string>
#include <stack>

template <typename T>
typename T::value_type pop(T& s)
{
    typename T::value_type top{s.top()};
        s.pop();
    
    return top;
}

void empty_cell() { std::cout << "|  \t"; }

template <typename T>
void top(T& s) { std::cout << "| " << pop(s) << '\t'; }

void title()
{
    std::cout << "-------------------------\n";
    std::cout << "|   a   |   b   |   c   |\n";
    std::cout << "-------------------------\n";
}

void stack_states(auto a, auto b, auto c)
{
    int size{3};
    
    title();
    
    while (size--)
    {
        if (a.size()) top(a);
        else empty_cell();
            
        if (b.size()) top(b);
		else empty_cell();
	   
	    if (c.size()) top(c);
		else empty_cell();
		    
		std::cout << "|\n";
    }
    
    std::cout << "-------------------------\n";
    std::cout << '\n';
}

template <typename T>
void hanoi_x(unsigned size, T& a, T& b, T& c)
{
    if (size)
    {
        hanoi_x(size - 1, a, c, b);
        c.push(pop(a));
        hanoi_x(size - 1, b, a, c);
    }
}

int main()
{
    std::stack<std::string> a{};
    std::stack<std::string> b{};
    std::stack<std::string> c{};
    
    a.push("cat");
    a.push("dog");
    a.push("sheep");
    
    stack_states(a, b, c);
    hanoi_x(a.size(), a, b, c);
    stack_states(a, b, c);
}