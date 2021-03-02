#ifndef VECTOR_VECTORITERATOR_H
#define VECTOR_VECTORITERATOR_H

#include "Vector.h"

template<class T>
class Vector<T>::Iterator : std::iterator<std::random_access_iterator_tag, T>
{
private:
    T *object_;

public:
    Iterator() : object_(nullptr)
    {};

    explicit Iterator(T *value) : object_(value)
    {}

    T *operator->()
    {
        return this->object_;
    }

    Iterator &operator++()
    {
        ++this->object_;
        return *this;
    }

    Iterator &operator--()
    {
        --this->object_;
        return *this;
    }

    T &operator*()
    {
        return *this->object_;
    }

    T operator*() const
    {
        return *this->object_;
    }

    bool operator==(const Iterator &other) const
    {
        return this->object_ == other.object_;
    }

    bool operator!=(const Iterator &other) const
    {
        return this->object_ != other.object_;
    }
};

#endif //VECTOR_VECTORITERATOR_H
