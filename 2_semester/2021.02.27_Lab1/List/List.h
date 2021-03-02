//
// Created by User on 28-Feb-21.
//

#ifndef INC_2021_02_27_LAB1_LIST_H
#define INC_2021_02_27_LAB1_LIST_H

#include <iostream>
#include <iterator>

using std::cout;


template<class T>
class List
{
private:
    class ListItem;

    ListItem *first_ = nullptr, *last_ = nullptr;
    unsigned int size_ = 0;

    void CopyListFrom(List<T> &);

public:
    class Iterator;

    List();

    List(const std::initializer_list<T> &);

    List(const List<T> &other);

    List(List<T> &&other) noexcept;

    void PushBack(const T &);

    void PushFront(const T &);

    void PopBack();

    void PopFront();

    unsigned int Size() const;

    void Print() const;

    bool Empty() const;

    Iterator begin();

    Iterator end();

    List<T> &operator=(List<T> &);

    List<T> &operator=(List<T> &&) noexcept;

};


#endif //INC_2021_02_27_LAB1_LIST_H
