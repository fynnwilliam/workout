#include "stack.h"

int main()
{
    try
    {
        stack<int> s{23};
        s.push(1);
        s.push(2);
        s.push(3);
        s.push(4);
        s.push(5);
        s.push(6);
        s.push(7);
        s.push(8);
        
        std::cout << s << "\n";
        std::cout << stack<float>{3} << "\n";
        
    }
    
    catch (std::exception const& e) { std::cout << e.what() << std::endl; }
}