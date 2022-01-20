#include "linked_list.h"

template <typename T>
std::size_t linked_list<T>::size() const noexcept
{
    return size_;
}

template <typename T>
void linked_list<T>::push_back(T const& item) noexcept
{
    if (size_++)
    {
        tail_->next = std::make_unique<node>(node{item});
        tail_->next->previous = tail_;
        tail_ = tail_->next.get();
    }
    else
    {
        head_ = std::make_unique<node>(node{item});
        tail_ = head_.get();
    }
}