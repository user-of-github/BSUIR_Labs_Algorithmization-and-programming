#include "MapFirst.h"


template<typename T1, typename T2>
constexpr typename MapFirst<T1, T2>::Iterator MapFirst<T1, T2>::begin()
{
    return Iterator(this, shared_ptr<typename MapFirst<T1, T2>::Node>(this->GetMinimumValue(this->root_)));
}

template<typename T1, typename T2>
constexpr typename MapFirst<T1, T2>::Iterator MapFirst<T1, T2>::end()
{
    return ++Iterator(this, this->GetMaximumValue(this->root_));
}


template<typename T1, typename T2>
MapFirst<T1, T2>::Iterator::Iterator():object_(shared_ptr<typename BinaryTree<T1, T2>::Node>(nullptr)), owner_(nullptr)
{}

template<typename T1, typename T2>
MapFirst<T1, T2>::Iterator::Iterator(BinaryTree<T1, T2> *owner,
                                     const shared_ptr<typename BinaryTree<T1, T2>::Node> object)
        : object_(object), owner_(owner)
{}

template<typename T1, typename T2>
shared_ptr<typename BinaryTree<T1, T2>::Node> MapFirst<T1, T2>::Iterator::operator->()
{
    return this->object_->value_;
}

template<typename T1, typename T2>
T2 &MapFirst<T1, T2>::Iterator::operator*()
{
    return ((this->object_->value_).second);
}

template<typename T1, typename T2>
constexpr T2 MapFirst<T1, T2>::Iterator::operator*() const
{
    return ((this->object_)->value_).second;
}

template<typename T1, typename T2>
typename MapFirst<T1, T2>::Iterator &MapFirst<T1, T2>::Iterator::operator++()
{
    this->object_ = (this->owner_)->NextElement(this->object_);
    return *this;
}

template<typename T1, typename T2>
const typename MapFirst<T1, T2>::Iterator MapFirst<T1, T2>::Iterator::operator++(int)
{
    auto temp = Iterator(this->owner_, this->object_);
    this->object_ = (this->owner_)->NextElement(this->object_);
    return temp;
}

template<typename T1, typename T2>
typename MapFirst<T1, T2>::Iterator &MapFirst<T1, T2>::Iterator::operator--()
{
    this->object_ = (this->owner_)->PreviousElement(this->object_);
    return *this;
}

template<typename T1, typename T2>
const typename MapFirst<T1, T2>::Iterator MapFirst<T1, T2>::Iterator::operator--(int)
{
    auto temp = Iterator(this->owner_, this->object_);
    this->object_ = (this->owner_)->PreviousElement(this->object_);
    return temp;
}

template<typename T1, typename T2>
bool MapFirst<T1, T2>::Iterator::operator==(const MapFirst<T1, T2>::Iterator &other) const
{
    return this->object_ == other.object_;
}

template<typename T1, typename T2>
bool MapFirst<T1, T2>::Iterator::operator!=(const MapFirst<T1, T2>::Iterator &other) const
{
    return this->object_ != other.object_;
}

template<typename T3, typename T4>
ostream &operator<<(ostream &os, const MapFirst<T3, T4> &element)
{
    os << "Map(" << element.size_ << "): {";
    element.RecursivePrint(element.root_, os);
    os << "}\n";

    return os;
}


