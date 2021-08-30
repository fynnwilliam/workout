#include <exception>

class array
{
private:
    int* arr_{nullptr};
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
    
    inline int size() const { return size_; }
    
    inline bool empty() const { return size_ == 0; }
    
    int& operator[](std::size_t index)
    { 
        if (!valid(index))
            throw std::out_of_range("invalid array index");
        
        return arr_[index];
    }
    
    int const& operator[](std::size_t index) const
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