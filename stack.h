#pragma once

#include "array.h"

template <typename T>
class stack
{
private:
    array<T> array_;
    int      top_{};
    
public:
    explicit stack(unsigned max_size) : array_{max_size}, top_{-1} {}
    
    void push(T const& elem)
    {
        if (size() == max_size())
            throw std::runtime_error("stack overflow");
        
        array_[++top_] = elem;
    }

    T pop()
    {
        if (!size())
            throw std::runtime_error("stack underflow");
            
        return array_[top_--];
    }
    
    T const& top() const
    {
        return size() ? array_[top_] : throw std::runtime_error("empty stack");
    }
    
    unsigned size() const { return top_ + 1; }
    
    bool empty() const { return size() == 0; }
    
    unsigned max_size() const { return array_.size(); }
    
    void clear() { top_ = -1; }
    
    friend std::ostream& operator<<(std::ostream& os, stack<T> const& s)
    {
        if (s.empty())
        {
            os << "  [*** empty stack ***]\n\n";
            
            return os;
        }
        
        os << "  [stack]\n";
        
        for (int i{s.top_}; i >= 0; --i)
            os << "   " << s.array_[i] << '\n';
            
        os << '\n';
        
        return os;
    }
};