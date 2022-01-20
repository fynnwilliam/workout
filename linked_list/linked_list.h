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

    node* head_{nullptr};
    node* tail_{nullptr};
    std::size_t size_{};

public:
    linked_list() = default;
};