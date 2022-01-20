#include "linked_list.h"

template <typename T>
std::size_t linked_list<T>::size() const noexcept
{
    return size_;
}
