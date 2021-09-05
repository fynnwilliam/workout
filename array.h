#pragma once

#include <exception>
#include <iostream>
#include <utility>

template <typename T>
class array
{
private:
    T* arr_{nullptr};
    unsigned  size_{};
    
public:
    array() = default;
    
    explicit array(unsigned size)
    {
        if (size)
        {
            arr_ = new T[size]{};
            size_ = size;
        }
    }
        
    array(array const& source)
    {
        if (!source.empty())
        {
            size_ = source.size();
            arr_ = new T[size_]{};
        
            for (unsigned i{}; i < size(); ++i)
                arr_[i] = source[i];
        }
    }
    
    array(array&& source) : arr_{source.arr_}, size_{source.size_}
    {
        source.arr_  = nullptr;
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
    
    inline unsigned size() const { return size_; }
    
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
    
    inline bool operator==(array const& rhs) const
    {
        return arr_ == rhs.arr_ && size_ == rhs.size_;
    }
    
    inline bool valid(std::size_t index) const
    {
        return index < size_;
    }

    T* begin() const { return arr_; }
    
    T* end() const { return size_ ? &arr_[size_] : arr_; }
    
    friend std::ostream& operator<<(std::ostream& os, array const& a)
    {
        os << "[ ";

        for (auto const& elem : a) os << elem << ' ';
        
        os << ']';
        
        return os;
    }
    
    ~array() { delete[] arr_; }
};