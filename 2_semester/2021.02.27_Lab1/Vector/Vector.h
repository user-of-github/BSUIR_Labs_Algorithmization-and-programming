//
// Created by User on 01-Mar-21.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <iterator>

template<class T>
class Vector
{
private:
    const unsigned int kStartCapacity = 4;

    T *array_;
    unsigned int size_, capacity_;

    void CopyArray(const T *, T *, const unsigned int &);

public:
    class Iterator;

    Vector();

    explicit Vector(const unsigned int &);

    Vector(const unsigned int &, const T &);

    Vector(const std::initializer_list<T> &);

    Vector(const Vector<T> &);

    Vector(Vector<T> &&) noexcept;

    ~Vector();

    void Resize(const unsigned int &);

    void PushBack(const T &);

    void PopBack();

    void Print() const;

    unsigned int Size() const;

    unsigned int Capacity() const;

    bool Empty() const;

    T operator[](const unsigned int &) const;

    Vector<T> &operator=(const Vector<T> &);

    Vector<T> &operator=(Vector<T> &&) noexcept;

    Iterator begin();

    Iterator end();
};


#endif //VECTOR_VECTOR_H
