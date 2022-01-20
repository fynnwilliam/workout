#include "linked_list.h"

template <typename T>
std::size_t linked_list<T>::size() const noexcept
{
    return size_;
}

template <typename T>
void linked_list<T>::push_back(T const& item) noexcept
{
    if (size())
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
    ++size;
}

template <typename T>
void linked_list<T>::push_front(T const& item) noexcept
{
    if (size())
    {
        auto temp{std::move(head_)};
        head_ = std::make_unique<node>(node{item});
        temp->previous = head_.get();
        head_->next = std::move(temp);
    }
    else
    {
        head_ = std::make_unique<node>(node{item});
        tail_ = head_.get();
    }
    ++size_;
}