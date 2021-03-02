#ifndef LIST_LISTITERATOR_H
#define LIST_LISTITERATOR_H

#include "List.h"

template<class T>
class List<T>::Iterator : std::iterator<std::bidirectional_iterator_tag, T>
{
private:
    ListItem *object_;

public:
    Iterator();

    explicit Iterator(ListItem *);

    ListItem *operator->();

    T &operator*();

    ListItem operator*() const;

    Iterator &operator++();

    Iterator &operator--();

    bool operator==(const Iterator &) const;

    bool operator!=(const Iterator &) const;
};


template<class T>
List<T>::Iterator::Iterator(): object_(nullptr)
{}

template<class T>
List<T>::Iterator::Iterator(ListItem *link): object_(link)
{}

template<class T>
T &List<T>::Iterator::operator*()
{
    return this->object_->value_;
}

template<class T>
typename List<T>::ListItem *List<T>::Iterator::operator->()
{
    return this->object_;
}

template<class T>
typename List<T>::ListItem List<T>::Iterator::operator*() const
{
    return *this->object_;
}

template<class T>
typename List<T>::Iterator &List<T>::Iterator::operator--()
{
    this->object_ = this->object_->previous_;
    return *this;
}

template<class T>
bool List<T>::Iterator::operator==(const List<T>::Iterator &it) const
{
    return this->object_ == it.object_;
}

template<class T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator &it) const
{
    return this->object_ != it.object_;
}

template<class T>
typename List<T>::Iterator &List<T>::Iterator::operator++()
{
    this->object_ = this->object_->next_;
    return *this;
}

#endif //LIST_LISTITERATOR_H