#include <cassert>

#include "stack.h"

int main()
{
    try
    {
        stack<int> s{10};
    
        std::cout << " created stack of max size: " << s.max_size() << '\n';
    
        while (true)
        {
            std::cout << " trying: stack.push(64);...";
            s.push(64);
            std::cout << " ok\n";
        }
    }
    
    catch (std::exception const& e) { std::cout << "\n " << e.what() << '\n'; }
}