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

    ListItem *first_, *last_;
    unsigned int size_;

public:
    class Iterator;

    List();

    List(const std::initializer_list<T> &);

    void PushBack(const T &);

    void PushFront(const T &);

    void PopBack();

    void PopFront();

    unsigned int Size() const;

    void Print() const;

    bool Empty() const;

    Iterator begin();

    Iterator end();

};


#endif //INC_2021_02_27_LAB1_LIST_H
