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
    
    inline int& operator[](int const& index) { return arr_[index]; }
    
    ~array() { delete[] arr_; }
};