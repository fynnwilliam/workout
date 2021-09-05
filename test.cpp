#include "stack.h"

int main()
{
    try
    {
        stack<int> s{23};
        std::cout << s.top() << '\n';
    }
    
    catch (std::exception const& e) { std::cout << e.what() << std::endl; }
}