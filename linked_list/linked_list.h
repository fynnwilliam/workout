#include <memory>
#include <cstddef>
#include <initializer_list>

template <typename T>
class linked_list
{
private:
    struct node
    {
        std::unique_ptr<node> next;
        node* previous;
        T data{};

        node() = default;
        node(T d) : data{d} {}
    };

    void initial_push(T const&) noexcept;
    void _push_front(T const&) noexcept;
    void _push_back(T const&) noexcept;

    std::unique_ptr<node> head_;
    node* tail_{nullptr};
    std::size_t size_{};

public:
    linked_list() = default;
    linked_list(std::initializer_list<T>);

    std::size_t size() const noexcept;

    bool empty() const noexcept;
    void push_back(T const&) noexcept;
    void push_front(T const&) noexcept;
};