#include <cstddef>
#include <initializer_list>

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
    linked_list(std::initializer_list<T>);

    std::size_t size() const noexcept;
};