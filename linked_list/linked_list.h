#include <cstddef>

template <typename T>
class linked_list
{
private:
    struct node
    {
        node* previous{nullptr};
        node* next{nullptr};
        T     data{};
    };

    node* head{nullptr};
    node* tail{nullptr};
    std::size_t size{};

public:
    linked_list() = default;
};