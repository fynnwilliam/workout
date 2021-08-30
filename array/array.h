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
        
    array(array const& rhs)
    {
        if (!rhs.empty())
        {
            size_ = rhs.size();
            arr_ = new int[size_]{};
        
            for (int i{}; i < size(); ++i)
                arr_[i] = rhs[i];
        }
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