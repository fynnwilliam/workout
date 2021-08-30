#pragma once

#include <exception>
#include <utility>

template <typename T>
class array
{
private:
    T* arr_{nullptr};
    int  size_{};
    
public:
    array() = default;
    
    explicit array(int size)
    {
        if (size > 0)
        {
            arr_ = new int[size]{};
            size_ = size;
        }
    }
        
    array(array const& source)
    {
        if (!source.empty())
        {
            size_ = source.size();
            arr_ = new T[size_]{};
        
            for (int i{}; i < size(); ++i)
                arr_[i] = source[i];
        }
    }
    
    array(array&& source) : arr_{source.arr_}, size_{source.size_}
    {
        source.arr_ = nullptr;
        source.size_ = 0;
    }
    
    array& operator=(array rhs)
    {
        swap(*this, rhs);
        
        return *this;
    }
    
    friend void swap(array& a, array& b) noexcept
    {
        std::swap(a.arr_, b.arr_);
        std::swap(a.size_, b.size_);
    }
    
    inline int size() const { return size_; }
    
    inline bool empty() const { return size_ == 0; }
    
    T& operator[](std::size_t index)
    { 
        if (!valid(index))
            throw std::out_of_range("invalid array index");
        
        return arr_[index];
    }
    
    T const& operator[](std::size_t index) const
    { 
        if (!valid(index))
            throw std::out_of_range("invalid array index");
            
        return arr_[index];
    }
    
    inline bool valid(std::size_t index) const
    {
        return index >= 0 && index <= size_;
    }
    
    friend std::ostream& operator<<(std::ostream& os, array const& a)
    {
        os << "[ ";
        
        for (int i = 0; i < a.size(); ++i)
            os << a[i] << ' ';
        
        os << ']';
        
        return os;
    }
    
    ~array() { delete[] arr_; }
};