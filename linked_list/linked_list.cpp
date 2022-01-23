#include "linked_list.h"

template <typename T>
std::size_t linked_list<T>::size() const noexcept
{
    return size_;
}

template <typename T>
bool linked_list<T>::empty() const noexcept
{
    return size() == 0;
}

template <typename T>
void linked_list<T>::push_back(T const& value) noexcept
{
    size() ? _push_back(value) : initial_push(value);
    ++size_;
}

template <typename T>
void linked_list<T>::push_front(T const& value) noexcept
{
    size() ? _push_front(item) : initial_push(item);
    ++size_;
}

template <typename T>
void linked_list<T>::initial_push(T const& item) noexcept
{
    head_ = std::make_unique<node>(node{item});
    tail_ = head_.get();
}

template <typename T>
void linked_list<T>::_push_front(T const& item) noexcept
{
    auto temp{std::move(head_)};
    head_ = std::make_unique<node>(node{item});
    temp->previous = head_.get();
    head_->next = std::move(temp);
}

template <typename T>
void linked_list<T>::_push_back(T const& item) noexcept
{
    tail_->next = std::make_unique<node>(node{item});
    tail_->next->previous = tail_;
    tail_ = tail_->next.get();
}