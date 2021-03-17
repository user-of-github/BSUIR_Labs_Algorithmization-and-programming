#ifndef INC_2021_02_27_LAB1_LIST_H
#define INC_2021_02_27_LAB1_LIST_H

#include <iostream>
#include <iterator>

using std::cout;
using std::size_t;
using std::ostream;

template<class T>
class List
{
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

    void Clear();

    size_t Size() const;

    bool Empty() const;

    Iterator begin();

    Iterator end();

    List<T> &operator=(const List<T> &);

    List<T> &operator=(List<T> &&) noexcept;

    template<typename T1>
    friend ostream &operator<<(ostream &, const List <T1> &);

private:
    class ListItem;

    ListItem *first_, *last_, *pseudo_last_;
    size_t size_;

    void CopyListFrom(const List<T> &);

    void CreatePseudoLast();

    void UpdatePseudoLast();
};

#endif //INC_2021_02_27_LAB1_LIST_H
