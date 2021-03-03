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

    ListItem *first_, *last_, *pseudo_last_;
    unsigned int size_;

    void CopyListFrom(const List<T> &);

    void CreatePseudoLast();

    void UpdatePseudoLast();

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

    List<T> &operator=(const List<T> &);

    List<T> &operator=(List<T> &&) noexcept;
};

#endif //INC_2021_02_27_LAB1_LIST_H
